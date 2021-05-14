// This file is a part of AtlasEngine
// CREATED : 08/05/2021
// UPDATED : 14/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	void StreamStack::tokenize(const char* file)
	{
		std::string data;
		std::string line;
		unsigned long line_count = 0;
		unsigned long index_count = 0;
		std::ifstream getter(file, std::ios::binary);
		if(getter)
		{
			while(std::getline(getter, line))
			{
				std::istringstream iss(line);
				while(iss >> data)
				{
					std::cout << data << " ";
					if(Token::keyword_token.count(data))
						_tokens.push_back(Token(Token::keyword_token[std::move(data)], line_count, index_count));
					else
						_tokens.push_back(Token(std::move(data), line_count, index_count));
					data.clear();
					index_count++;
				}
				std::cout << std::endl;
				line_count++;
				index_count = 0;
			}
			getter.close();
		}
		else
		{
			ELTMerrors error = file_not_found_error(file, 0);
			std::cout << error.what() << std::endl;
		}
	}

	Token StreamStack::getToken(int line, int index)
	{
		int returner = 0;
		for(int i = 0; i < _tokens.size(); i++)
		{
			std::cout << _tokens[i].getLine() << "	" << _tokens[i].getIndex() << std::endl;
			if(_tokens[i].getLine() == line && _tokens[i].getIndex() == index)
			{
				returner = i;
				break;
			}
		}
		if(returner > _tokens.size())
		{
			ELTMerrors error = context_error("token getter out of bounds", 0);
			std::cout << error.what() << std::endl;
			return Token(error.what(), 0, 0);
		}
		return _tokens[returner];
	}

	int StreamStack::getLineIndexNumber(int line)
	{
		int returner = 0;
		for(int i = line;; i++)
		{
			if(_tokens[i].getLine() != line)
			{
				returner = i-1;
				break;
			}
		}
		return returner;
	}

	int StreamStack::getTokenNumber()
	{
		return _tokens.size();
	}
}

