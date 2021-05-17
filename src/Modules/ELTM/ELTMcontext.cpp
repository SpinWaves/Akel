// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 17/05/2021

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
		for(int i = 0; i <= _stream.getLineNumber(); i++)
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
							_imports[_stream.getToken(i, 1).getString()] = newFile;
							if(!_imports[_stream.getToken(i, 1).getString()].newContext(_stream.getToken(i, 1).getString().c_str()))
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
		_isError = false;
		return true;
	}

	bool ELTMcontext::setID(int line)
	{
		std::string text;
		if(_stream.getToken(line, 2).getReservedToken() == assign)
		{
			for(int j = 3; j <= _stream.getLineIndexNumber(line); j++)
			{
				text += _stream.getToken(line, j).getString();
				text += " ";
			}
			_texts[_stream.getToken(line, 1).getString()] = text;
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

