// This file is a part of AtlasEngine
// CREATED : 06/05/2021
// UPDATED : 06/05/2021

#include <MTML.h>

namespace AE
{
	const std::map<std::string, mtml_token> keyword_token
	{
		{"set", mtml_token::kw_set},
		{"=", mtml_token::assign},
		{"get", mtml_token::kw_get},

		{"import", mtml_token::kw_import},

		{"begin", mtml_token::kw_begin},
		{"end", mtml_token::kw_end},

		{"module", mtml_token::kw_module},

		{"//", mtml_token::kw_basic_comment},
		{"/*", mtml_token::begin_long_comment},
		{"*/", mtml_token::end_long_comment}
	};

	Token::Token(std::variant<mtml_token, std::string> value, size_t line, size_t index)
	{
		_value = std::move(value);
		_line = line;
		_index = index;
	}

	bool Token::isString()
	{
		return std::holds_alternative<std::string>(_value);
	}
	bool Token::isKeyword()
	{	
		return std::holds_alternative<mtml_token>(_value);
	}

	std::string getString()
	{
		return std::get<std::string>(_value);
	}
	mtml_token getReservedToken()
	{
		return std::get<mtml_token>(_value);
	}
	size_t Token::getLine()
	{
		return _line;
	}
	size_t Token::getIndex()
	{
		return _index;
	}
}

