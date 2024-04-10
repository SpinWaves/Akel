// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/04/2024
// Updated : 10/04/2024

#ifndef __AK_UTILS_CALL_ON_EXIT__
#define __AK_UTILS_CALL_ON_EXIT__

#include <Utils/PreCompiled.h>

namespace Ak
{
	template <typename F>
	class CallOnExit
	{
		public:
			CallOnExit() = default;
			CallOnExit(F&& functor);
			CallOnExit(const CallOnExit&) = delete;
			CallOnExit(CallOnExit&&) = delete;

			void CallAndReset();
			void Reset();

			CallOnExit& operator=(const CallOnExit&) = delete;
			CallOnExit& operator=(CallOnExit&&) = default;

			~CallOnExit();

		private:
			std::optional<F> m_functor;
	};

	template<typename F>
	CallOnExit(F) -> CallOnExit<F>;
}

#include <Utils/CallOnExit.inl>

#endif
