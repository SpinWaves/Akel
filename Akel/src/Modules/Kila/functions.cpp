// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 25/10/2022

#include "functions.h"
#include "compiler.h"
#include "compiler_context.h"
#include "errors.h"
#include "lexer.h"
#include "token_iterator.h"

namespace Ak::Kl
{
	void compile_function_block(compiler_context& ctx, tk_iterator& it, type_handle return_type_id);

	function_declaration parse_function_declaration(compiler_context& ctx, tk_iterator& it)
	{
		function_declaration ret;

		parse_token_value(it, Tokens::kw_function);

		function_type ft;
		ret.name = parse_declaration_name(ctx, it, true);

		{
			auto _ = ctx.function();

			parse_token_value(it, Tokens::bracket_b);

			while(!it->has_value(Tokens::bracket_e))
			{
				if(!ret.params.empty())
					parse_token_value(it, Tokens::comma);

				std::string name = parse_declaration_name(ctx, it, false);
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
			if(it->has_value(Tokens::embrace_b))
				nesting++;

			if(it->has_value(Tokens::embrace_e))
				nesting--;

			_tokens.push_back(*it);
			++it;
		}

		if(nesting)
			unexpected_syntax_error("end of file", it->get_line_number()).expose();

		ctx.create_function(_decl.name, _decl.type_id);
	}

	function_body::function_body(function_body&& orig) noexcept : _tokens(std::move(orig._tokens)), _decl(std::move(orig._decl)) {}

	void function_body::compile(compiler_context& ctx)
	{
		ctx.function();
		const function_type* ft = std::get_if<function_type>(_decl.type_id);
		for(int i = 0; i < int(_decl.params.size()); i++)
			ctx.create_param(std::move(_decl.params[i]), ft->param_type_id[i].type_id);
		tk_iterator it(_tokens);
		compile_function_block(ctx, it, ft->return_type_id);
	}
}
