// This file is a part of AtlasEngine
// CREATED : 08/05/2021
// UPDATED : 08/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	void StreamStack::tokenize(const char* file)
	{
		std::string data;
		int c = 0;
		long line_count = 0;
		long long index_count = 0;
		std::ifstream getter(file, std::ios::binary);
		if(getter)
		{
			while(getter >> data)
			{
				c = getter.peek();
				if(c == '\n')
				{
					line_count++;
					index_count = 0;
				}
				if(keyword_token.count(data))
					_tokens.push_back(Token(std::move(data), line_count, index_count));
				data.clear();
				index_count++;
			}
			getter.close();
		}
		else
			std::cout << "eltm error" << std::endl;
	}

	Token StreamStack::getToken(int line, int index)
	{
		int returner;
		for(int i = 0; i < _tokens.size(); i++)
		{
			std::cout << _tokens[i].getLine() << "		" << _tokens[i].getIndex() << std::endl;
			if(_tokens[i].getLine() == line && _tokens[i].getIndex() == index)
			{
				std::cout << "	" << _tokens[i].isKeyword() << std::endl;
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

