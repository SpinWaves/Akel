// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 07/05/2021

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
            inline void add_file(std::string file) { _files.push_back(std::move(file)); }
            inline std::vector<std::string>& get_files() { return _files; }

            ~StreamStack() = default;

        private:
            std::vector<std::string> _files;
            std::stack<int> _stack;
            const func::function<int()>& _input;
            size_t _line;
    };
}

#endif // __AK_KILA_STREAM_STACK__
