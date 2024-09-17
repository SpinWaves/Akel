// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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
