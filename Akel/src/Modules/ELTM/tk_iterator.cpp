// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 27/08/2022

#include "tk_iterator.h"
#include "streamStack.h"

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
