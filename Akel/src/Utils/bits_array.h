// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2022
// Updated : 11/11/2022

#ifndef __AK_BITS_ARRAY__
#define __AK_BITS_ARRAY__

#include <Akpch.h>
#include <Core/profile.h>
#include "nonCopyable.h"

namespace Ak
{
#ifdef AK_64BITS
using uintsys_t = uint64_t;
#else
using uintsys_t = uint32_t;
#endif

	class BitsArray : public non_copyable
	{
		public:
			BitsArray(size_t bits_n);

			void resetBits(bool value);
			void set(size_t index, bool value);
			bool get(size_t index) const;

			~BitsArray() = default;

			static constexpr uintsys_t nbits = CHAR_BIT / sizeof(uintsys_t);

		private:
			std::unique_ptr<uintsys_t[]> _pool;
			size_t _size = 0;
	};
}

#endif
