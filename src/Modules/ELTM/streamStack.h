// This file is a part of AtlasEngine
// CREATED : 07/05/2021
// UPDATED : 14/05/2021

#ifndef __STREAM_STACK__
#define __STREAM_STACK__

#include <AEpch.h>
#include <Modules/ELTM/token.h>
#include <Utils/utils.h>

namespace AE
{
	class StreamStack
	{
		public:
			void tokenize(const char* source, std::string file, std::string caller, size_t line_error)
			{
				std::string data;
				std::string line;
				unsigned long line_count = 0;
				unsigned long index_count = 0;
				std::ifstream getter(source, std::ios::binary);
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
					std::string message = source;
					message.append(" file not found");
					ELTMerrors error = context_error(message, file, caller, line_error);
					std::cout << red << error.what() << def << std::endl;
				}
			}

			Token getToken(int line, int index, std::string file, std::string caller, size_t line_error)
			{
				int returner = 0;
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
					ELTMerrors error = context_error("token getter out of bounds", file, caller, line_error);
					std::cout << red << error.what() << def << std::endl;
					return Token(error.what(), 0, 0);
				}
				return _tokens[returner];
			}
			
			int getTokenNumber();
			int getLineIndexNumber(int line);

		private:
			std::vector<Token> _tokens;
	};

	#undef tokenize
	#define tokenize(file) tokenize(file, __FILE__, __FUNCTION__, __LINE__)
	#undef getToken
	#define getToken(line, index) getToken(line, index, __FILE__, __FUNCTION__, __LINE__)
}

#endif // __STREAM_STACK__

