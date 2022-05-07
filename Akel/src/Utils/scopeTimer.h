// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/04/2022
// Updated : 07/05/2022

#ifndef __AK_SCOPE_TIMER__
#define __AK_SCOPE_TIMER__

#include <Akpch.h>
#include "nonCopyable.h"

namespace Ak
{
	class ScopeTimer : public non_copyable
	{
		public:
			ScopeTimer(const char* scope_name);
			~ScopeTimer();

		private:
			const char* _scope_name = nullptr;
			const std::chrono::steady_clock::time_point _start;
	};
}

#endif // __AK_SCOPE_TIMER__
