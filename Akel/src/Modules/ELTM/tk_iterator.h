// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/08/2022
// Updated : 26/08/2022

#include <Akpch.h>
#include "token.h"

namespace Ak
{
	class tk_iterator
	{
		public:
			tk_iterator(std::deque<Token>& tokens);
			tk_iterator(class StreamStack& tokens);

			inline const Token& operator*() const noexcept { return _current; }
			inline const Token* operator->() const noexcept { return &_current; }
			inline tk_iterator& operator++() noexcept { _current = _get_next_token(); return *this; }
			inline tk_iterator operator++(int) noexcept
			{
				tk_iterator old = *this;
				operator++();
				return old;
			}
			inline bool operator()() const noexcept { return !_current.is_eof(); }

		private:
			Token _current;
			func::function<Token()> _get_next_token;
	};
}
