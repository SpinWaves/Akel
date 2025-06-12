// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_STREAM_STACK_H
#define AK_STREAM_STACK_H

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

#endif // AK_STREAM_STACK_H
