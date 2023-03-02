// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/03/2023
// Updated : 02/03/2023

#ifndef __AK_CALL_ON_EXIT__
#define __AK_CALL_ON_EXIT__

#include <Akpch.h>

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

			void callAndReset();
			void reset();

			CallOnExit& operator=(const CallOnExit&) = delete;
			CallOnExit& operator=(CallOnExit&&) = default;

			~CallOnExit();
			
		private:
			std::optional<F> _functor = std::nullopt;
	};

	template<typename F>
	CallOnExit(F) -> CallOnExit<F>;
}

#include <Utils/call_on_exit.inl>

#endif
