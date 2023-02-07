// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 27/01/2023

#include <Akpch.h>
#include <Modules/ELTM/token.h>
#include <Modules/ELTM/streamStack.h>
#include <Modules/ELTM/ELTMerrors.h>

namespace Ak
{
	enum class char_type
	{
		eof,
		space,
		alphanum,
		punct,
	};

	char_type get_char_type(int c)
	{
		if(c < 0)
			return char_type::eof;
		if(std::isspace(c))
			return char_type::space;
		if(std::isalpha(c) || std::isdigit(c) || char(c) == '_' || char(c) == '"')
			return char_type::alphanum;
		return char_type::punct;
	}

	Token fetch_word(StreamStack& stream)
	{
		std::size_t line = stream.getline();

		std::string word;

		int c = stream();

		if(c == '"')
		{
			do
			{
				c = stream();
				if(c == '\n')
					continue;
				if(get_char_type(c) == char_type::eof)
					unexpected_error("end of file", stream.getfile(), stream.getline()).expose();
				if(c == '\\')
				{
					switch(c = stream())
					{
						case '\\': c = '\\'; break;
						case 'n': c = '\n';  break;
						case 't': c = '\t';  break;
						case 'r': c = '\r';  break;
						case '"': c = '"';   break;

						default: break;
					}
				}
				word.push_back(char(c));
			} while(c != '"');
			word.pop_back();
			return Token(std::move(word), line);
		}

		do
		{
			word.push_back(char(c));
			c = stream();
		} while(get_char_type(c) == char_type::alphanum);

		stream.push_back(c);

		if(std::optional<eltm_token> t = get_keyword(word))
			return Token(*t, line);
		return Token(identifier{std::move(word)}, line);
	}

	Token fetch_operator(StreamStack& stream)
	{
		std::size_t line = stream.getline();

		if(std::optional<eltm_token> t = get_operator(stream))
			return Token(*t, line);

		std::string unexpected;
		std::size_t err_line_number = stream.getline();
		for(int c = stream(); get_char_type(c) == char_type::punct; c = stream())
			unexpected.push_back(char(c));
		unexpected_error(std::move(unexpected), stream.getfile(), err_line_number).expose();
	}

	void skip_line_comment(StreamStack& stream)
	{
		int c = 0;
		do
		{
			c = stream();
		} while(c != '\n' && get_char_type(c) != char_type::eof);

		if(c != '\n')
			stream.push_back(c);
	}

	void skip_block_comment(StreamStack& stream)
	{
		bool closing = false;
		int c = 0;
		int line = stream.getline();
		do
		{
			c = stream();
			if(closing && c == '/')
				return;
			closing = (c == '*');
		} while(get_char_type(c) != char_type::eof);

		stream.push_back(c);
	}

	Token lexe(StreamStack& stream)
	{
		for(;;)
		{
			std::size_t line = stream.getline();
			int c = stream();

			switch(get_char_type(c))
			{
				case char_type::space: continue;
				case char_type::eof: return {eof(), line};
				case char_type::alphanum: stream.push_back(c); return fetch_word(stream);
				case char_type::punct:
				{
					switch(c)
					{
						case '/':
						{
							char c1 = stream();
							switch(c1)
							{
								case '/': skip_line_comment(stream); continue;
								case '*': skip_block_comment(stream); continue;

								default: stream.push_back(c1);
							}
						}

						default: stream.push_back(c); return fetch_operator(stream);
					}
				}
				break;
			}
		}
	}
}
