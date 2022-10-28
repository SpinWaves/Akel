// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 28/10/2022

#include "file.h"
#include "compiler.h"
#include "errors.h"
#include "token_iterator.h"
#include "stream_stack.h"
#include "compiler_context.h"
#include "functions.h"
#include "spirv_data.h"
#include "spirv_part.h"

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
		if(!_it->is_keyword())
			unexpected_syntax(it).expose();
		
		type_handle t = nullptr;
		
		switch(_it->get_token())
		{
			case Tokens::t_num: t = ctx.get_handle(simple_type::number); break;
			case Tokens::t_void: t = ctx.get_handle(simple_type::nothing); break;
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

	std::string parse_declaration_name(compiler_context& _ctx, tk_iterator& it, bool is_function)
	{
		if(!_it->is_identifier())
			unexpected_syntax(_it).expose();

		std::string ret = _it->get_identifier().name;

		if(!_ctx.can_declare(ret, is_function))
			already_declared_error(ret.c_str(), _it->get_line_number()).expose();

		++it;

		return ret;
	}

	void Compiler::compile_variable_declaration()
    {
        std::string name = parse_declaration_name(_ctx, _it, false);

        type_handle type_id = nullptr;
        if(_it->has_value(Tokens::type_specifier))
        {
            parse_token_value(_it, Tokens::type_specifier);
            type_id = parse_type(_ctx, _it);

            if(type_id == type_registry::get_void_handle())
                syntax_error("cannot declare void variable", _it->get_line_number()).expose();

			if(_it->has_value(Tokens::square_b))
			{
				++it;
				parse_token_value(_it, Tokens::square_e);
				type_id = _ctx.get_handle(array_type{type_id});
			}
        }

        std::vector<expression<lvalue>::ptr> ret;

        if(_it->has_value(Tokens::assign))
        {
            ++_it;
            ret.emplace_back(build_initialization_expression(_ctx, _it, type_id, false));
        }
        else
            ret.emplace_back(build_default_initialization(type_id));

        _ctx.create_identifier(std::move(name), type_id);

        return ret;
    }

	void Compiler::compile_statement()
    {
        if(_it->is_keyword())
        {
            switch(_it->get_token())
            {
                case Tokens::kw_for:       return compile_for_statement();
                case Tokens::kw_while:     return compile_while_statement();
                case Tokens::statement_if: return compile_if_statement();
                case Tokens::kw_break:     return compile_break_statement();
                case Tokens::kw_return:    return compile_return_statement();

                default: break;
            }
        }
		else if(_it->is_identifier() && _ctx.can_declare(_it->get_identifier().name, false))
			return compile_var_statement();

        if(_it->has_value(Tokens::embrace_b))
            return compile_block_statement();
        return compile_simple_statement();
    }

	void Compiler::compile_simple_statement()
    {
		parse_token_value(_it, Tokens::endline);
    }

	void Compiler::compile_while_statement()
    {
		parse_token_value(_it, Tokens::kw_while);

		bool brackets = false;

		if(_it->has_value(Tokens::bracket_b))
		{
			parse_token_value(_it, Tokens::bracket_b);
			brackets = true;
		}

		if(brackets)
			parse_token_value(_it, Tokens::bracket_e);

		parse_token_value(_it, Tokens::kw_do);
		compile_block_statement();
    }

	void Compiler::compile_for_statement()
	{
		parse_token_value(_it, Tokens::kw_for);

		bool brackets = false;

		if(_it->has_value(Tokens::bracket_b))
		{
			parse_token_value(_it, Tokens::bracket_b);
			brackets = true;
		}

		if(brackets)
			parse_token_value(_it, Tokens::bracket_e);

		parse_token_value(_it, Tokens::kw_do);
		compile_block_statement();
	}

	void Compiler::compile_return_statement()
    {
        parse_token_value(_it, Tokens::kw_return);

        if(pf.return_type_id == type_registry::get_void_handle())
        {
            parse_token_value(_it, Tokens::semicolon);
            return create_return_void_statement();
        }
        parse_token_value(_it, Tokens::endline);
    }

    void Compiler::compile_block_statement()
    {
		_ctx.scope();
        if(_it->has_value(Tokens::embrace_b))
        {
            parse_token_value(_it, Tokens::embrace_b);

            while(!_it->has_value(Tokens::embrace_e))
                ret.push_back(compile_statement(_ctx, _it));

            parse_token_value(_it, Tokens::embrace_e);
        }
        else
            ret.push_back(compile_statement(_ctx, _it));
    }

	void Compiler::compile_function_declaration(function_body fn)
	{
		SpirvPart part;
		part.add(Spv::OpFunction, /* return type id*/, /*fn id*/, 0, /*fn type id*/);
		_code.insert(_code.end(), part.begin(), part.end());
	}

	std::vector<uint32_t> Compiler::generateSpirV(const std::string& code)
	{
		func::function<int()> get = [&]()
		{
			static size_t pos = 0;
			return code[pos++];
		};

		StreamStack stream(&get);
		_it = tk_iterator(stream);

		std::vector<function_body> function_bodys;

		while(_it())
		{
			if(!std::holds_alternative<Tokens>(_it->get_value()))
	            unexpected_syntax(_it).expose();

			switch(_it->get_token()) // global scope
			{
				case Tokens::kw_function:
				{
					function_bodys.emplace_back(context, _it);
					compile_function_declaration(function_bodys.back());
					break;
				}

				default: compile_variable_declaration() break;
			}
		}

		for(function_body& f : function_bodys)
			f.compile();

		return _code;
	}
}
