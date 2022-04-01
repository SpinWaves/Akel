// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/04/2022
// Updated : 01/04/2022

#include "scopeTimer.h"

namespace Ak
{
	ScopeTimer::ScopeTimer(const char* scope_name) : _scope_name(scope_name), _start(std::chrono::steady_clock::now()) {}

	ScopeTimer::~ScopeTimer()
	{
		auto stop = std::chorno::steady_clock::now();
		auto duration = stop - _start;
		auto ms = std::chorno::duration_cast<std::chorno::milliseconds>(duration).count();
		std::cout << ms << " ms " << _scope_name << std::endl;
	}
}
