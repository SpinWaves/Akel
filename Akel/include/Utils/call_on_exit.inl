// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/03/2023
// Updated : 02/03/2023

#include <Utils/call_on_exit.h>

namespace Ak
{
	template<typename F>
	CallOnExit<F>::CallOnExit(F&& functor) : functor(std::move(functor)) {}

	template<typename F>
	CallOnExit<F>::~CallOnExit()
	{
		if(functor)
			(*functor)();
	}

	template<typename F>
	void CallOnExit<F>::CallAndReset()
	{
		if(functor)
			(*functor)();

		functor.reset();
	}

	template<typename F>
	void CallOnExit<F>::Reset()
	{
		functor.reset();
	}
}
