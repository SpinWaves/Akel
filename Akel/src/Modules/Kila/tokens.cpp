// This file is a part of Akel
// CREATED : 09/11/2021
// UPDATED : 11/11/2021

#include <Modules/Kila/tokens.h>

namespace Ak::Kl
{
	std::optional<Tokens> get_keyword(const std::string& word)
	{
		if(!Token::kw_tokens.have(word))
			return std::nullopt;
		return std::make_optional(Token::kw_tokens[word]);
	}

	std::optional<Tokens> get_operator(StreamStack& stream)
	{
		std::string c;
		c.push_back(char(stream()));
		if(!Token::operators_token.have(c))
			return std::nullopt;
		return std::make_optional(Token::operators_token[std::move(c)]);
	}

    Token::Token(token_value value, unsigned int line, unsigned int index) : _value(std::move(value)), _line(line), _index(index) {}

	bool operator==(const identifier& id1, const identifier& id2)
    {
		return id1.name == id2.name;
	}
	
	bool operator!=(const identifier& id1, const identifier& id2)
    {
		return id1.name != id2.name;
	}
	
	bool operator==(const eof&, const eof&)
    {
		return true;
	}
	
	bool operator!=(const eof&, const eof&)
    {
		return false;
	}
}
