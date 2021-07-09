// This file is a part of Akel
// CREATED : 12/05/2021
// UPDATED : 08/07/2021

#include <Modules/ELTM/eltm.h>

namespace Ak
{
	ELTMcontext::ELTMcontext() : _stream()
	{
		_comments[0] = false;
		_comments[1] = false;
	}

	bool ELTMcontext::newContext(std::string file)
	{
		_file = file.c_str();
		_stream.tokenize(_file);
		static std::string __ELTM_MAIN_FILE;
		std::string import_file;
		std::string text;

		std::string path;
		std::size_t found = 0;
		found = file.rfind("/");
		path.append(file.begin(), file.begin() + found + 1);

		if(__ELTM_MAIN_FILE.empty())
			__ELTM_MAIN_FILE = file;

		for(_line = 0; _line < _stream.getLineNumber(); _line++)
		{
			if(!_comments[0] && !_comments[1])
			{
				if(_stream.getToken(_line, 0).isKeyword())
				{
					switch(_stream.getToken(_line, 0).getReservedToken())
					{
						case kw_set:
						{
							if(_stream.getToken(_line, 1).isString())
							{
								if(_texts.count(_stream.getToken(_line, 1).getString()))
								{
									ELTMerrors error = already_declared_error(_stream.getToken(_line, 1).getString(), file, _line + 1);
									std::cout << red << error.what() << def << std::endl;
									_isError = true;
									return false;
								}
								if(!setID(true))
									return false;
							}
							else
							{				
								ELTMerrors error = syntax_error("ID name cannot be a keyword", file, _line + 1);
								std::cout << red << error.what() << def << std::endl;
								_isError = true;
								return false;
							}
							break;
						}
						case kw_import:
						{
							if(_stream.getToken(_line, 1).isString())
							{
								bool isKnown = false;
								if(_stream.getToken(_line, 1).getString() == __ELTM_MAIN_FILE)
									isKnown = true;
								else
								{
									for(auto elem : _imports)
									{
										if(elem.getFile() == _stream.getToken(_line, 1).getString().c_str())
										{
											isKnown = true;
											break;
										}
									}
								}
								if(!isKnown)
								{
									ELTMcontext newFile;
									_imports.push_back(newFile);
									if(!_imports.back().newContext(std::string(path + _stream.getToken(_line, 1).getString()).c_str()))
									{
										_isError = true;
										return false;
									}
								}
							}
							else
							{
								ELTMerrors error = syntax_error("file name cannot be a keyword", file, _line + 1);
								std::cout << red << error.what() << def << std::endl;
								_isError = true;
								return false;
							}
							break;
						}
						case basic_comment: _comments[0] = true; break;
						case begin_long_comment: _comments[1] = true; _last_line_long_comment = _line; break;
						
						case kw_begin:
						{
							if(_stream.getToken(_line, 1).isKeyword())
							{
								if(_stream.getToken(_line, 1).getReservedToken() == kw_module)
								{
									if(!_lastModuleName.empty())
									{
										ELTMerrors error = simple_error("module cannot be instancied inside another module", _file, _line+1);
										std::cout << red << error.what() << def << std::endl;
										_isError = true;
										return false;
									}
									if(_stream.getToken(_line, 2).isString())
									{
										_lastModuleName = _stream.getToken(_line, 2).getString();
									}
									else
									{
										ELTMerrors error = syntax_error("module name cannot be a keyword", _file, _line+1);
										std::cout << red << error.what() << def << std::endl;
										_isError = true;
										return false;
									}
								}
							}
							else
							{
								ELTMerrors error = syntax_error("keyword as \"module\" needed after \"begin\"", _file, _line+1);
								std::cout << red << error.what() << def << std::endl;
								_isError = true;
								return false;
							}
							break;
						}
						case kw_end:
						{
							if(_stream.getToken(_line, 1).isKeyword())
							{
								if(_stream.getToken(_line, 1).getReservedToken() == kw_module)
									_lastModuleName.clear();
							}
						}

						default: break;
					}
				}
				else 
				{
					Token::activateKw(false); 
					if(_stream.getToken(_line, 0).getString() == "___ELTM_TOKEN_COMMENT_BASIC_CODE___")
					{
						_comments[0] = true;
						Token::activateKw();
					}
					else if(!_texts.count(_stream.getToken(_line, 0).getString()))
					{
						Token::activateKw();
						ELTMerrors error = simple_error(std::string("undefined ID or keyword \"" + _stream.getToken(_line, 0).getString() + "\""), file, _line + 1);
						std::cout << red << error.what() << def << std::endl;
						_isError = true;
						return false;
					}
					if(!setID(false))
						return false;
				}
			}
			if(_comments[0])
				_comments[0] = false;
			if(_comments[1])
			{
				if(_stream.getToken(_line, 0).isKeyword())
				{
					if(_stream.getToken(_line, 0).getReservedToken() == end_long_comment)
						_comments[1] = false;
				}
			}

		}
		if(_comments[1])
		{
			ELTMwarning warning = no_end("long comment (/*)", file, _last_line_long_comment);
			std::cout << magenta << warning.what() << def << std::endl;
		}
		_isError = false;
		return true;
	}

	bool ELTMcontext::setID(bool isNewID)
	{
		std::string text;
		std::string moduleName;
		std::string moduleID;
		int found;
		bool long_text = false;
		int assignPos = 0;
		bool getText = false;

		if(isNewID)
			assignPos = 2;
		else
			assignPos = 1;
		int j = assignPos + 1;

		if(_stream.getToken(_line, assignPos).getReservedToken() == assign)
		{
			int currentLine = _line;
			Token::activateKw(false);
			
			while(_line < _stream.getLineNumber())
			{
				for(;j < _stream.getLineIndexNumber(_line); j++)
				{
					// Comment check
					if(_stream.getToken(_line, j).getString() == Token::mixable_keywords_token[basic_comment])
						_comments[0] = true;
					if(_stream.getToken(_line, j).getString() == Token::mixable_keywords_token[begin_long_comment])
					{
						_comments[1] = true;
						_last_line_long_comment = _line;
					}

					if(!_comments[0] && !_comments[1])
					{
						if(_stream.getToken(_line, j).getString() == Token::mixable_keywords_token[kw_get] && _stream.getToken(_line, j+1).getString() == Token::mixable_keywords_token[begin_long_text])
							getText = true;

						// Long text begin check
						if(_stream.getToken(_line, j).getString() == Token::mixable_keywords_token[begin_long_text] && !getText)
						{
							if(j != assignPos + 1)
							{
								ELTMerrors error = syntax_error("long text key \"(\" needs to be at the begenning of a text", _file, _line + 1);
								std::cout << red << error.what() << def << std::endl;
								_isError = true;
								return false;
							}
							else
								long_text = true;
						}
						else if(_stream.getToken(_line, j).getString() == Token::mixable_keywords_token[end_long_text] && long_text) // Check for long text end
							long_text = false;
						else
						{
							if(getText)
							{
								if(_stream.getToken(_line, j + 3).getString() == Token::mixable_keywords_token[end_long_text])
								{
									if(_texts.count(_stream.getToken(_line, j + 2).getString()))
									{
										text = _texts[_stream.getToken(_line, j + 2).getString()];
										break;
									}
									if((found = _stream.getToken(_line, j + 2).getString().find(".")) != std::string::npos)
									{
										moduleName.append(_stream.getToken(_line, j + 2).getString(), 0, found);
										if(_modules.count(moduleName))
										{
											moduleID.append(_stream.getToken(_line, j + 2).getString(), found + 1, _stream.getToken(_line, j + 2).getString().length());
											if(_modules[moduleName].count(moduleID))
											{
												text = _modules[moduleName][moduleID];
												break;
											}
										}
										else
										{
											ELTMerrors error = simple_error("\"get()\" : undefined module name", _file, _line + 1);
											std::cout << red << error.what() << def << std::endl;
											_isError = true;
											return false;
										}
									}

									ELTMerrors error = simple_error("\"get()\" : undefined ID", _file, _line + 1);
									std::cout << red << error.what() << def << std::endl;
									_isError = true;
									return false;
								}
								else
								{
									ELTMerrors error = simple_error("get ID begun without end", _file, _line + 1);
									std::cout << red << error.what() << def << std::endl;
									_isError = true;
									return false;
								}
							}
							else
							{
								// Get text needed
								text += _stream.getToken(_line, j).getString();
								text += " ";
							}
						}
					}

					if(_stream.getToken(_line, j).getString() == Token::mixable_keywords_token[end_long_comment] && _comments[1])
						_comments[1] = false;
				}

				if(!long_text)
					break;
				_line++;
				j = 0;
			}
			if(_lastModuleName.empty())
				_texts[_stream.getToken(currentLine, assignPos - 1).getString()] = text;
			else
				_modules[_lastModuleName][_stream.getToken(currentLine, assignPos - 1).getString()] = text;

			Token::activateKw();
			if(long_text)
			{
				ELTMwarning warning = no_end("long text (\"(\")", _file, currentLine + 1);
				std::cout << magenta << warning.what() << def << std::endl;
			}
		}
		else
		{
			ELTMerrors error = syntax_error("missing \"=\" after ID declaration", _file, _line + 1);
			std::cout << red << error.what() << def << std::endl;
			_isError = true;
			return false;
		}
		return true;
	}
}

