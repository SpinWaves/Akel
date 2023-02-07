// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/04/2022
// Updated : 27/01/2023

#include <Utils/scopeTimer.h>

namespace Ak
{
	ScopeTimer::ScopeTimer(const char* scope_name) : _scope_name(scope_name), _start(std::chrono::steady_clock::now()) {}

	ScopeTimer::~ScopeTimer() { std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start).count() << " ms " << _scope_name << std::endl; }
}
