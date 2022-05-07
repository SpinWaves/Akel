// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/11/2021
// Updated : 07/05/2021

#include <Modules/Kila/token_iterator.h>
#include <Modules/Kila/lexer.h>

namespace Ak::Kl
{
    tk_iterator::tk_iterator(StreamStack& stream) : _current(eof(), 0), _get_next_token([&stream](){ return lexe(stream); })
	{
		++(*this);
	}
	
	tk_iterator::tk_iterator(std::deque<Token>& tokens) : _current(eof(), 0),
														_get_next_token([&tokens]()
														{
															if(tokens.empty())
																return Token(eof(), 0);
															Token ret = std::move(tokens.front());
															tokens.pop_front();
															return ret;
														})
	{
		++(*this);
	}
}
