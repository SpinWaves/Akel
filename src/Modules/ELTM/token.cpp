// This file is a part of AtlasEngine
// CREATED : 06/05/2021
// UPDATED : 08/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	const std::map<std::string, eltm_token> keyword_token
	{
		{"set", eltm_token::kw_set},
		{"=", eltm_token::assign},
		{"get", eltm_token::kw_get},

		{"import", eltm_token::kw_import},

		{"begin", eltm_token::kw_begin},
		{"end", eltm_token::kw_end},

		{"module", eltm_token::kw_module},

		{"//", eltm_token::basic_comment},
		{"/*", eltm_token::begin_long_comment},
		{"*/", eltm_token::end_long_comment}
	};

	Token::Token(std::variant<eltm_token, std::string> value, size_t line, size_t index)
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
		return std::holds_alternative<eltm_token>(_value);
	}

	std::string Token::getString()
	{
		return std::get<std::string>(_value);
	}
	eltm_token Token::getReservedToken()
	{
		return std::get<eltm_token>(_value);
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

