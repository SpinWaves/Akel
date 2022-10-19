// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 19/10/2022

#include "functions.h"
#include "compiler.h"
#include "compiler_context.h"
#include "errors.h"
#include "lexer.h"
#include "token_iterator.h"

namespace Ak::Kl
{
	function_declaration parse_function_declaration(compiler_context& ctx, tk_iterator& it)
	{
		function_declaration ret;

		parse_token_value(it, Tokens::kw_function);

		function_type ft;
		ret.name = parse_declaration_name(ctx, it);

		{
			auto _ = ctx.function();

			parse_token_value(it, Tokens::bracket_b);

			while(!it->has_value(Tokens::bracket_e))
			{
				if(!ret.params.empty())
					parse_token_value(it, Tokens::comma);

				std::string name = parse_declaration_name(ctx, it);
				ret.params.push_back(name);

				parse_token_value(it, Tokens::colon);

				type_handle t = parse_type(ctx, it);

				ft.param_type_id.push_back({t});
			}
			++it;
		}

		parse_token_value(it, Tokens::arrow);
		ft.return_type_id = parse_type(ctx, it);

		if(it->has_value(Tokens::square_b))
		{
			++it;
			parse_token_value(it, Tokens::square_e);
			ft.return_type_id = ctx.get_handle(table_type{ft.return_type_id});
		}

		ret.type_id = ctx.get_handle(ft);

		return ret;
	}

	function_body::function_body(compiler_context& ctx, tk_iterator& it)
	{
		_decl = parse_function_declaration(ctx, it);

		_tokens.push_back(*it);

		int nesting = 1;

		while(nesting && !it->is_eof())
		{
			if(it->is_keyword())
			{
				switch(it->get_token())
				{
					case Tokens::statment_then:
					case Tokens::statment_else:
					case Tokens::kw_do: nesting++; break;

					case Tokens::kw_end: nesting--; break;

					default : break;
				}
			}
			_tokens.push_back(*it);
			++it;
		}

		if(nesting)
			unexpected_syntax_error("end of file", it->get_line_number()).expose();

		ctx.create_function(_decl.name, _decl.type_id);
	}

	function_body::function_body(function_body&& orig) noexcept : _tokens(std::move(orig._tokens)), _decl(std::move(orig._decl)) {}
}
