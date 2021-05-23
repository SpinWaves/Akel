// This file is a part of AtlasEngine
// CREATED : 07/05/2021
// UPDATED : 23/05/2021

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
				_tokens.clear();

				std::string data;
				std::string subData;
				std::string line;
				int line_count = 0;
				int index_count = 0;
				size_t found = 0;
				std::vector<std::pair<int, Token>> tempo;

				std::ifstream getter(source, std::ifstream::in);
				if(getter.is_open())
				{
					while(std::getline(getter, line)) // get entire line from file
					{	
						std::istringstream iss(line);
						while(iss >> data)			// get word after word from the line
						{
							/*for(auto const elem : Token::keyword_token)
							{
								if((found = data.find(elem) != std::string::npos)
								{
									subData = data;
									if(found == 0)
									{
										subData.erase(subData.begin() + found, subData.end());
										tempo.push_back(std::make_pair(index_count, Token(Token::keyword_token[std::move(subData)])));
										index_count++;
									}
								}
							}*/
							if(Token::keyword_token.have(data))
								tempo.push_back(std::make_pair(index_count, Token(Token::keyword_token[std::move(data)])));
							else
								tempo.push_back(std::make_pair(index_count, Token(std::move(data))));
							index_count++;
						}
						if(!tempo.empty())
						{
							_tokens[line_count] = tempo; // push tokens with indexes in _tokens at line number
							line_count++;
							index_count = 0;
							tempo.clear();
						}
					}
					getter.close();
				}
				else
				{
					std::string message = source;
					message.append(" file not found");
					ELTMerrors error = context_error(std::move(message), file, caller, line_error);
					std::cout << red << error.what() << def << std::endl;
				}
			}

			Token getToken(int line, int index, std::string file, std::string caller, size_t line_error)
			{
				if(_tokens.count(line))
				{
					for(auto const elem : _tokens[line])	// for the std::vector, for loop is needed
					{
						if(std::get<0>(elem) == index) // elem is a std::pair from the std::vector
							return std::get<1>(elem); // return the Token from the std::pair
					}
				}
				ELTMerrors error = context_error("token getter out of bounds", file, caller, line_error);
				std::cout << red << error.what() << def << std::endl;
				return Token("error");
			}
			
			int getTokenNumber();
			int getLineIndexNumber(int line);
			int getLineNumber();

		private:
			std::unordered_map<int, std::vector<std::pair<int, Token>>> _tokens;
			/*
				_tokens architecture :
				line0	index0 Token
						index1 Token
						index2 Token

				line1   index0 Token 
						index1 Token
				
				line2	index0 Token
						index1 Token
						index2 Token
					  ...
			*/
	};

	#undef tokenize
	#define tokenize(file) tokenize(file, __FILE__, __FUNCTION__, __LINE__)
	#undef getToken
	#define getToken(line, index) getToken(line, index, __FILE__, __FUNCTION__, __LINE__)
}

#endif // __STREAM_STACK__

