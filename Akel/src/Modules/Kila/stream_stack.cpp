// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 11/11/2021

#include <Modules/Kila/stream_stack.h>

namespace Ak::Kl
{
    StreamStack::StreamStack(const func::function<int()>* input) : _input(*input), _line(0), _index(0) {}
	
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
		
		_index++;
		
		return ret;
	}
	
	void StreamStack::push_back(int c) 
    {
		_stack.push(c);
		
		if(c == '\n')
			_line--;
		
		_index--;
	}
}
