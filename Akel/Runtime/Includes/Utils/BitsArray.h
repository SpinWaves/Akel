// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2024
// Updated : 04/03/2024

#ifndef __AK_UTILS_BITS_ARRAY__
#define __AK_UTILS_BITS_ARRAY__

#include <Utils/PreCompiled.h>
#include <Utils/NonCopyable.h>

namespace Ak
{
	#ifdef AK_64BITS
		using uintsys_t = uint64_t;
	#else
		using uintsys_t = uint32_t;
	#endif

	class BitsArray : public NonCopyable
	{
		public:
			BitsArray() = default;

			inline void Init(std::size_t bits_n);
			inline void ResetBits(bool value);
			inline void Set(std::size_t index, bool value);
			inline bool Get(std::size_t index) const;
			inline std::size_t GetFirstTrueBit();

			~BitsArray() = default;

			static constexpr uintsys_t nbits = CHAR_BIT * sizeof(uintsys_t);

		private:
			std::unique_ptr<uintsys_t[]> m_pool;
			std::size_t m_size = 0;
	};
}

#include <Utils/BitsArray.inl>

#endif
