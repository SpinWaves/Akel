// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
