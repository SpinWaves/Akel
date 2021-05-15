// This file is a part of AtlasEngine
// CREATED : 12/05/2021
// UPDATED : 15/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMcontext::ELTMcontext() : _stream()
	{}

	bool ELTMcontext::newContext(const char* file)
	{
		_stream.tokenize(file);
		std::string text;
		for(int i = 0; i <= _stream.getLineNumber(); i++)
		{
			if(_stream.getToken(i, 0).isKeyword())
			{
				switch(_stream.getToken(i, 0).getReservedToken())
				{
					case kw_set:
					{
						if(_stream.getToken(i, 2).getReservedToken() == assign)
						{
							for(int j = 3; j <= _stream.getLineIndexNumber(i); j++)
							{
								text += _stream.getToken(i, j).getString();
								text += " ";
							}
							_texts[_stream.getToken(i, 1).getString()] = text;
						}
						else
						{
							ELTMerrors error = syntax_error("missing \"=\" after ID declaration", file, _stream.getToken(i, 0).getLine()+1);
							std::cout << red << error.what() << def << std::endl;
							_isError = true;
							return false;
						}
						break;
					}

					default: break;
				}
			}
		}
		_isError = false;
		return true;
	}
}

