// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 12/11/2021

#ifndef __AK_KILA_STREAM_STACK__
#define __AK_KILA_STREAM_STACK__

#include <Akpch.h>

namespace Ak::Kl
{
    class StreamStack
    {
        public:
            explicit StreamStack(const func::function<int()>* input);
            
            int operator()();
            
            void push_back(int c);
            
            inline size_t getline() const noexcept { return _line; }
            inline size_t getindex() const noexcept { return _index; }

            ~StreamStack() = default;

        private:
            const func::function<int()>& _input;
            std::stack<int> _stack;
            size_t _line;
            size_t _index;
    };
}

#endif // __AK_KILA_STREAM_STACK__
