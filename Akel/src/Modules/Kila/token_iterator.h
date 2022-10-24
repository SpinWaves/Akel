// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/11/2021
// Updated : 24/10/2022

#ifndef __AK_KILA_TOKEN_ITERATOR__
#define __AK_KILA_TOKEN_ITERATOR__

#include <Modules/Kila/tokens.h>
#include <Akpch.h>

namespace Ak::Kl
{
    class StreamStack;

    class tk_iterator
    {
        public:
			tk_iterator() = default;
            tk_iterator(std::deque<Token>& tokens);
            tk_iterator(StreamStack& tokens);

			tk_iterator& operator=(tk_iterator&&) noexcept = default;

            inline const Token& operator*() const noexcept { return _current; }
            inline const Token* operator->() const noexcept { return &_current; }
            inline bool operator()() const noexcept { return !_current.is_eof(); }
            inline tk_iterator& operator++()
            {
                _current = _get_next_token();
                return *this;
            }
            inline tk_iterator operator++(int)
            {
                tk_iterator old = *this;
                operator++();
                return old;
            }
	
        private:
            Token _current;
            func::function<Token()> _get_next_token;
    };
}

#endif // __AK_KILA_TOKEN_ITERATOR__
