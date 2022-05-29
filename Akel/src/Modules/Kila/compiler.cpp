// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 29/05/2022

#include "file.h"
#include "compiler.h"
#include "errors.h"
#include "token_iterator.h"
#include "stream_stack.h"
#include "compiler_context.h"

namespace Ak::Kl
{
	std::vector<uint32_t> Compiler::generateSpirV(const std::string& code)
	{
		func::function<int()> get = [&]()
		{
			static size_t pos = 0;
			return code[pos++];
		};

		StreamStack stream(&get);
		tk_iterator it(stream);
	}

	std::string Compiler::loadFile(const std::string& path)
	{
		File f(path.c_str());
		std::string ret;
		while(!f.is_eof())
			ret.push_back((char)f());
		return ret;
	}

	inline Error unexpected_syntax(const tk_iterator& it)
	{
		return unexpected_syntax_error(std::to_string(it->get_value()).c_str(), it->get_line_number());
	}

	type_handle parse_type(compiler_context& ctx, tk_iterator& it)
	{
		if(!it->is_keyword())
			unexpected_syntax(it).expose();
		
		type_handle t = nullptr;
		
		switch(it->get_token())
		{
			case Tokens::t_void:
				t = ctx.get_handle(simple_type::nothing);
				++it;
			break;
			case Tokens::t_num:
				t = ctx.get_handle(simple_type::number);
				++it;
			break;
			case Tokens::t_bool:
				t = ctx.get_handle(simple_type::boolean);
				++it;
			break;

			default: unexpected_syntax(it).expose();
		}
		
		while(it->is_keyword())
		{
			switch(it->get_token())
			{
				case Tokens::square_b:
					parse_token_value(++it, Tokens::square_e);
					t = ctx.get_handle(table_type{t});
				break;
				
				default: return t;
			}
		}
		
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
}
