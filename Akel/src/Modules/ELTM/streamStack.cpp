// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/05/2021
// Updated : 26/08/2022

#include "streamStack.h"

namespace Ak
{
	StreamStack::StreamStack(const func::function<int()>* input, std::string file) : _input(*input), _file(std::move(file)) {}

	int StreamStack::operator()()
	{
		int ret = -1;

		if(_stack.empty())
			ret = _input();
		else
		{
			ret = _stack.top();
			_stack.pop();
		}

		if(ret == '\n')
			_line++;

		return ret;
	}

	void StreamStack::push_back(int c)
	{
		_stack.push(c);
		if(c == '\n')
			_line--;
	}
}

