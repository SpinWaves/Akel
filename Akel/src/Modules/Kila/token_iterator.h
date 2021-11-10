// This file is a part of Akel
// CREATED : 10/11/2021
// UPDATED : 10/11/2021

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
            tk_iterator(std::deque<Token>& tokens);
            tk_iterator(StreamStack& tokens);

            tk_iterator(const tk_iterator&) = delete;

            void operator=(const tk_iterator&) = delete;

            inline const Token& operator*() const
            {
                return _current;
            }
            inline const Token* operator->() const
            {
                return &_current;
            }
            inline tk_iterator& operator++()
            {
                _current = _get_next_token();
                return *this;
            }
            inline explicit operator bool() const
            {
                return !_current.is_eof();
            }
	
        private:
            Token _current;
            std::function<Token()> _get_next_token;
    };
}

#endif // __AK_KILA_TOKEN_ITERATOR__
