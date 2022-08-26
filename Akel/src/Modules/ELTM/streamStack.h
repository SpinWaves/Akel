// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/05/2021
// Updated : 26/08/2022

#ifndef __AK_STREAM_STACK__
#define __AK_STREAM_STACK__

#include <Akpch.h>

namespace Ak
{
	class StreamStack
	{
		public:
			StreamStack(const func::function<int()>* input, std::string file);

			int operator()();

			void push_back(int c);

			inline std::size_t getline() const noexcept { return _line; }
			inline const std::string& getfile() const noexcept { return _file; }

			~StreamStack() = default;

		private:
			const func::function<int()>& _input;
			std::stack<int> _stack;
			std::string _file;
			std::size_t _line = 0;
	};
}

#endif // __AK_STREAM_STACK__
