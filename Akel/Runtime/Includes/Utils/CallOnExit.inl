// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#pragma once
#include <Utils/CallOnExit.h>

namespace Ak
{
	template<typename F>
	CallOnExit<F>::CallOnExit(F&& functor) : m_functor(std::move(functor)) {}

	template<typename F>
	CallOnExit<F>::~CallOnExit()
	{
		if(m_functor)
			(*m_functor)();
	}

	template<typename F>
	void CallOnExit<F>::CallAndReset()
	{
		if(m_functor)
			(*m_functor)();
		m_functor.reset();
	}

	template<typename F>
	void CallOnExit<F>::Reset()
	{
		m_functor.reset();
	}
}
