// This file is a part of AtlasEngine
// CREATED : 08/05/2021
// UPDATED : 11/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	void StreamStack::tokenize(const char* file)
	{
		std::string data;
		std::string line;
		eltm_token kw;
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
					if(Token::keyword_token.count(data))
						_tokens.push_back(Token(Token::keyword_token[std::move(data)], line_count, index_count));
					else
						_tokens.push_back(Token(std::move(data), line_count, index_count));
					data.clear();
					index_count++;
				}
				line_count++;
				index_count = 0;
			}
			getter.close();
		}
		else
			std::cout << "eltm error : can't open " << file  << std::endl;
	}

	Token StreamStack::getToken(int line, int index)
	{
		int returner;
		for(int i = 0; i < _tokens.size(); i++)
		{
			if(_tokens[i].getLine() == line && _tokens[i].getIndex() == index)
			{
				returner = i;
				break;
			}
		}
		if(returner > _tokens.size())
		{
			std::cout << "eltm error" << std::endl;
			return Token("error", 0, 0);
		}
		return _tokens[returner];
	}
}

