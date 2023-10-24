// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/10/2023
// Updated : 24/10/2023

#ifndef __AK_WINDOWS_OS__
#define __AK_WINDOWS_OS__

#include <Akpch.h>

namespace Ak
{
	class AK_API WindowsOS
	{
		public:
			WindowsOS() = default;
			void init() noexcept;
			void shutdown() noexcept;
			~WindowsOS() = default;

		private:
	};
}

#endif
