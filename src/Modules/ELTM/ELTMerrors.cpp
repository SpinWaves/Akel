// This file is a part of AtlasEngine
// CREATED : 13/05/2021
// UPDATED : 13/05/2021

#include <Modules/ELTM/eltm.h>

namespace AE
{
	ELTMerrors::ELTMerrors(std::string message, size_t line)
	{
		_message = std::move(message);
		_line = line;
	}

	const char* ELTMerrors::what()
	{
		return _message.c_str();
	}

	size_t ELTMerrors::line()
	{
		return _line;
	}
}

