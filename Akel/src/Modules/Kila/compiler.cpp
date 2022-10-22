// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 22/10/2022

#include "file.h"
#include "compiler.h"
#include "errors.h"
#include "token_iterator.h"
#include "stream_stack.h"
#include "compiler_context.h"
#include <functions.h>

namespace Ak::Kl
{
	inline Error unexpected_syntax(const tk_iterator& it)
	{
		return unexpected_syntax_error(std::to_string(it->get_value()).c_str(), it->get_line_number());
	}

	std::string Compiler::loadFile(const std::string& path)
	{
		File f(path.c_str());
		std::string ret;
		while(!f.is_eof())
			ret.push_back((char)f());
		return ret;
	}

	type_handle parse_type(compiler_context& ctx, tk_iterator& it)
	{
		if(!it->is_keyword())
			unexpected_syntax(it).expose();
		
		type_handle t = nullptr;
		
		switch(it->get_token())
		{
			case Tokens::t_void: t = ctx.get_handle(simple_type::nothing); break;
			case Tokens::t_num:  t = ctx.get_handle(simple_type::number); break;
			case Tokens::t_bool: t = ctx.get_handle(simple_type::boolean); break;

			default: unexpected_syntax(it).expose();
		}

		it++;
		
		return t;
	}

	void parse_token_value(tk_iterator& it, const token_value& value)
	{
		if(it->has_value(value))
		{
			++it;
			return;
		}
		expected_syntax_error(std::to_string(value).c_str(), it->get_line_number()).expose();
	}

	std::string parse_declaration_name(compiler_context& ctx, tk_iterator& it)
	{
		if(!it->is_identifier())
			unexpected_syntax(it).expose();

		std::string ret = it->get_identifier().name;

		if(!ctx.can_declare(ret))
			already_declared_error(ret.c_str(), it->get_line_number()).expose();

		++it;

		return ret;
	}

	std::vector<expression<lvalue>::ptr> compile_variable_declaration(compiler_context& ctx, tk_iterator& it)
    {
        std::string name = parse_declaration_name(ctx, it);

        type_handle type_id = nullptr;
        if(it->has_value(Tokens::type_specifier))
        {
            parse_token_value(ctx, it, Tokens::type_specifier);
            type_id = parse_type(ctx, it);

            if(type_id == type_registry::get_void_handle())
                syntax_error("cannot declare void variable", it->get_line_number()).expose();

			if(it->has_value(Tokens::square_b))
			{
				++it;
				parse_token_value(ctx, it, Tokens::square_e);
				type_id = ctx.get_handle(array_type{type_id});
			}
        }

        std::vector<expression<lvalue>::ptr> ret;

        if(it->has_value(Tokens::assign))
        {
            ++it;
            ret.emplace_back(build_initialization_expression(ctx, it, type_id, false));
        }
        else
            ret.emplace_back(build_default_initialization(type_id));

        ctx.create_identifier(std::move(name), type_id);

        return ret;
    }

	std::vector<uint32_t> Compiler::generateSpirV(const std::string& code)
	{
		func::function<int()> get = [&]()
		{
			static size_t pos = 0;
			return code[pos++];
		};

		StreamStack stream(&get);
		tk_iterator it(stream);

		compiler_context context;

		std::vector<function_body> function_bodys;
		std::vector<expression<lvalue>::ptr> initializers;

		while(it())
		{
			if(!std::holds_alternative<Tokens>(it->get_value()))
	            unexpected_syntax(it).expose();

			switch(it->get_token()) // global scope
			{
				case Tokens::kw_function: function_bodys.emplace_back(context, it); break;

				default:
					for(expression<lvalue>::ptr& expr : compile_variable_declaration(context, it))
						initializers.push_back(std::move(expr));
				break;
			}
		}
	}
}
