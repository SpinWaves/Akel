// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 01/02/2024

#include <Plugins/ELTM/PreCompiled.h>
#include <Plugins/ELTM/Token.h>
#include <Plugins/ELTM/StreamStack.h>
#include <Plugins/ELTM/Errors.h>

namespace Ak
{
	enum class CharType
	{
		eof,
		space,
		alphanum,
		punct,
	};

	CharType GetCharType(int c)
	{
		if(c < 0)
			return CharType::eof;
		if(std::isspace(c))
			return CharType::space;
		if(std::isalpha(c) || std::isdigit(c) || char(c) == '_' || char(c) == '"')
			return CharType::alphanum;
		return CharType::punct;
	}

	Token FetchWord(StreamStack& stream)
	{
		std::size_t line = stream.GetLine();

		std::string word;

		int c = stream();

		if(c == '"')
		{
			do
			{
				c = stream();
				if(c == '\n')
					continue;
				if(GetCharType(c) == CharType::eof)
					UnexpectedError("end of file", stream.GetFile(), stream.GetLine()).Expose();
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
		} while(GetCharType(c) == CharType::alphanum);

		stream.push_back(c);

		if(std::optional<EltmToken> t = GetKeyword(word))
			return Token(*t, line);
		return Token(Identifier{std::move(word)}, line);
	}

	Token FetchOperator(StreamStack& stream)
	{
		std::size_t line = stream.GetLine();

		if(std::optional<EltmToken> t = GetOperator(stream))
			return Token(*t, line);

		std::string unexpected;
		std::size_t err_line_number = stream.GetLine();
		for(int c = stream(); GetCharType(c) == CharType::punct; c = stream())
			unexpected.push_back(char(c));
		UnexpectedError(std::move(unexpected), stream.GetFile(), err_line_number).Expose();
		return Token(Eof{}, line);
	}

	void SkipLineComment(StreamStack& stream)
	{
		int c = 0;
		do
		{
			c = stream();
		} while(c != '\n' && GetCharType(c) != CharType::eof);

		if(c != '\n')
			stream.push_back(c);
	}

	void SkipBlockComment(StreamStack& stream)
	{
		bool closing = false;
		int c = 0;
		int line = stream.GetLine();
		do
		{
			c = stream();
			if(closing && c == '/')
				return;
			closing = (c == '*');
		} while(GetCharType(c) != CharType::eof);

		stream.push_back(c);
	}

	Token Lexe(StreamStack& stream)
	{
		for(;;)
		{
			std::size_t line = stream.GetLine();
			int c = stream();

			switch(GetCharType(c))
			{
				case CharType::space: continue;
				case CharType::eof: return {Eof(), line};
				case CharType::alphanum: stream.push_back(c); return FetchWord(stream);
				case CharType::punct:
				{
					switch(c)
					{
						case '/':
						{
							char c1 = stream();
							switch(c1)
							{
								case '/': SkipLineComment(stream); continue;
								case '*': SkipBlockComment(stream); continue;

								default: stream.push_back(c1);
							}
						}

						default: stream.push_back(c); return FetchOperator(stream);
					}
				}
				break;
			}
		}
	}
}
