// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/11/2021
// Updated : 13/11/2021

#include <Modules/Kila/tokens.h>

namespace Ak::Kl
{
	std::optional<Tokens> get_keyword(const std::string& word)
	{
		if(!Token::kw_tokens.have(word))
			return std::nullopt;
		return std::make_optional(Token::kw_tokens[word]);
	}

	std::optional<Macro_Tokens> get_macro(const std::string& word)
	{
		if(!Token::macros_token.have(word))
			return std::nullopt;
		return std::make_optional(Token::macros_token[word]);
	}

	std::optional<Tokens> get_operator(StreamStack& stream)
	{
		std::string c;
		c.push_back(char(stream()));
		c.push_back(char(stream()));
		if(Token::operators_token.have(c))
			return std::make_optional(Token::operators_token[std::move(c)]);

		stream.push_back(c[1]);
		c.pop_back();
		if(Token::operators_token.have(c))
			return std::make_optional(Token::operators_token[std::move(c)]);

		return std::nullopt;
	}

    Token::Token(token_value value, unsigned int line) : _value(std::move(value)), _line(line) {}
}
