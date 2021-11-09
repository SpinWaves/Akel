// This file is a part of Akel
// CREATED : 09/11/2021
// UPDATED : 09/11/2021

#include <Modules/Kila/tokens.h>

namespace Ak::Kl
{
    Token::Token(token_value value, unsigned int line, unsigned int index) : _value(std::move(value)), _line(line), _index(index) {}
	
	bool Token::is_keyword() const
    {
		return std::holds_alternative<Tokens>(_value);
	}
	
	bool Token::is_identifier() const
    {
		return std::holds_alternative<identifier>(_value);
	}
	
	bool Token::is_number() const
    {
		return std::holds_alternative<double>(_value);
	}
	
	bool Token::is_string() const
    {
		return std::holds_alternative<std::string>(_value);
	}
	
	bool Token::is_eof() const
    {
		return std::holds_alternative<eof>(_value);
	}
	
	Tokens Token::get_token() const
    {
		return std::get<Tokens>(_value);
	}
	
	const identifier& Token::get_identifier() const
    {
		return std::get<identifier>(_value);
	}
	
	double Token::get_number() const
    {
		return std::get<double>(_value);
	}
	
	const std::string& Token::get_string() const
    {
		return std::get<std::string>(_value);
	}
	
	const token_value& Token::get_value() const
    {
		return _value;
	}
	
	size_t Token::get_line_number() const
    {
		return _line;
	}

	size_t Token::get_char_index() const
    {
		return _index;
	}
	
	bool Token::has_value(token_value value) const
    {
		return _value == std::move(value);
	}
	
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
