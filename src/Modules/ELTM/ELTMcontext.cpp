// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 20/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMcontext::ELTMcontext() : _stream()
	{}

	bool ELTMcontext::newContext(const char* file)
	{
		_file = file;
		_stream.tokenize(file);
		std::string import_file;
		for(int i = 0; i < _stream.getLineNumber(); i++)
		{
			if(!_comments[0] && !_comments[1])
			{
				if(_stream.getToken(i, 0).isKeyword())
				{
					switch(_stream.getToken(i, 0).getReservedToken())
					{
						case kw_set:
						{
							if(_stream.getToken(i, 1).isString())
							{
								if(_texts.count(_stream.getToken(i, 1).getString()))
								{
									ELTMerrors error = already_declared_error(_stream.getToken(i, 1).getString(), file, i + 1);
									std::cout << red << error.what() << def << std::endl;
									_isError = true;
									return false;
								}
								if(!setID(i))
									return false;
							}
							else
							{				
								ELTMerrors error = syntax_error("ID name cannot be a keyword", file, i + 1);
								std::cout << red << error.what() << def << std::endl;
								_isError = true;
								return false;
							}
							break;
						}
						case kw_import:
						{
							if(_stream.getToken(i, 1).isString())
							{
								ELTMcontext newFile;
								_imports.push_back(newFile);
								if(!_imports.back().newContext(_stream.getToken(i, 1).getString().c_str()))
								{
									_isError = true;
									return false;
								}
							}
							else
							{
								ELTMerrors error = syntax_error("file name cannot be a keyword", file, i + 1);
								std::cout << red << error.what() << def << std::endl;
								_isError = true;
								return false;
							}
							break;
						}
						case basic_comment: _comments[0] = true; break;
						case begin_long_comment: _comments[1] = true; break;

						default: break;
					}
				}
				else 
				{
					if(!_texts.count(_stream.getToken(i, 0).getString()))
					{
						ELTMerrors error = syntax_error(std::string("segmentation fault : undefined ID \"" + _stream.getToken(i, 0).getString()), file, i + 1);
						std::cout << red << error.what() << def << std::endl;
						_isError = true;
						return false;
					}
					if(!setID(i))
						return false;
				}
			}
			if(_comments[0])
				_comments[0] = false;
			if(_comments[1])
			{
				if(_stream.getToken(i, 0).isKeyword())
				{
					if(_stream.getToken(i, 0).getReservedToken() == end_long_comment)
						_comments[1] = false;
				}
			}

		}
		_isError = false;
		return true;
	}

	bool ELTMcontext::setID(int line)
	{
		std::string text;
		size_t found;
		if(_stream.getToken(line, 2).getReservedToken() == assign)
		{
			Token::activateKw(false);
			for(int j = 3; j < _stream.getLineIndexNumber(line); j++)
			{
				if(_stream.getToken(line, j).getString() == "___ELTM_TOKEN_COMMENT_BASIC_CODE___")
					_comments[0] = true;
				if(_stream.getToken(line, j).getString() == "___ELTM_TOKEN_COMMENT_LONG_BEGIN_CODE___")
					_comments[1] = true;

				if(!_comments[0] && !_comments[1])
				{
					text += _stream.getToken(line, j).getString();
					if((found = text.find("//")) != std::string::npos)
					{
						text.erase(found, text.size());
						_comments[0] = true;
					}
					if((found = text.find("/*")) != std::string::npos)
					{
						if(text.find("*/") != std::string::npos)
							text.erase(found, text.find("*/"));
						else
						{
							text.erase(found, text.size());
							_comments[1] = true;
						}
					}
					text += " ";
				}
				if(_stream.getToken(line, j).getString().find("*/") != std::string::npos && _comments[1])
						_comments[1] = false;

				if(_stream.getToken(line, j).getString() == "___ELTM_TOKEN_COMMENT_LONG_END_CODE___")
					_comments[1] = false;
			}
			_texts[_stream.getToken(line, 1).getString()] = text;
			Token::activateKw();
		}
		else
		{
			ELTMerrors error = syntax_error("missing \"=\" after ID declaration", _file, line + 1);
			std::cout << red << error.what() << def << std::endl;
			_isError = true;
			return false;
		}
		return true;
	}
}

