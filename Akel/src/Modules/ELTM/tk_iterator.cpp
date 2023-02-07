// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 27/01/2023

#include <Modules/ELTM/tk_iterator.h>
#include <Modules/ELTM/streamStack.h>

namespace Ak
{
	Token lexe(StreamStack& stream);

	tk_iterator::tk_iterator(StreamStack& stream) :
		_current(eof(), 0),
		_get_next_token([&stream]() { return lexe(stream); })
	{
		++(*this);
	}
}
