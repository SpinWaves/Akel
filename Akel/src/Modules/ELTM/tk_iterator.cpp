// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 26/08/2022

#include "tk_iterator.h"
#include "streamStack.h"

namespace Ak
{
	Token lexe(StreamStack& stream);

	tk_iterator::tk_iterator(StreamStack& stream) : _current(eof(), 0), _get_next_token([&stream](){ return lexe(stream); }) { ++(*this); }

	tk_iterator::tk_iterator(std::deque<Token>& tokens) : _current(eof(), 0),
		_get_next_token([&tokens]()
		{
			if(tokens.empty())
				return Token(eof(), 0);
			Token ret = std::move(tokens.front());
			tokens.pop_front();
			return ret;
		})
	{ ++(*this); }
}
