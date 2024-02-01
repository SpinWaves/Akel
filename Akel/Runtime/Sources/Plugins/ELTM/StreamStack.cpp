// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/05/2021
// Updated : 01/02/2024

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

