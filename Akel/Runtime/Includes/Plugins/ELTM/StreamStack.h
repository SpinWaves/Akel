// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/05/2021
// Updated : 01/02/2024

#ifndef __AK_STREAM_STACK__
#define __AK_STREAM_STACK__

#include <Plugins/ELTM/PreCompiled.h>

namespace Ak
{
	class StreamStack
	{
		public:
			StreamStack(const func::function<int()>* input, std::string file);

			int operator()();
			void push_back(int c);

			inline std::size_t GetLine() const noexcept { return m_line; }
			inline const std::string& GetFile() const noexcept { return m_file; }

			~StreamStack() = default;

		private:
			const func::function<int()>& m_input;
			std::stack<int> m_stack;
			std::string m_file;
			std::size_t m_line = 0;
	};
}

#endif // __AK_STREAM_STACK__
