// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 01/02/2024

#include <Plugins/ELTM/TkIterator.h>
#include <Plugins/ELTM/StreamStack.h>

namespace Ak
{
	Token Lexe(StreamStack& stream);

	TkIterator::TkIterator(StreamStack& stream) : m_current(Eof(), 0), m_get_next_token([&stream]() { return Lexe(stream); })
	{
		++(*this);
	}
}
