// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Plugins/ELTM/StreamStack.h>

namespace Ak
{
	StreamStack::StreamStack(const func::function<int()>* input, std::string file) : m_input(*input), m_file(std::move(file)) {}

	int StreamStack::operator()()
	{
		int ret = -1;

		if(m_stack.empty())
			ret = m_input();
		else
		{
			ret = m_stack.top();
			m_stack.pop();
		}

		if(ret == '\n')
			m_line++;

		return ret;
	}

	void StreamStack::push_back(int c)
	{
		m_stack.push(c);
		if(c == '\n')
			m_line--;
	}
}

