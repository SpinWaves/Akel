// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once
#include <Utils/BitsArray.h>

#include <Core/Logs.h>

namespace Ak
{
	void BitsArray::Init(std::size_t bits_n)
	{
		m_size = (nbits + bits_n - 1) / nbits;
		m_pool.reset(new uintsys_t[m_size]);
		std::memset(m_pool.get(), 0, m_size);
	}

	void BitsArray::ResetBits(bool value)
	{
		std::memset(m_pool.get(), value ? 255 : 0, m_size);
	}

	void BitsArray::Set(std::size_t index, bool value)
	{
		const uintsys_t i = index / nbits;
		if(i > m_size)
		{
			Error("Bits Array set : index out of range");
			return;
		}
		#ifdef AK_64BITS
			const uintsys_t mask = 1ULL << (index % nbits);
		#else
			const uintsys_t mask = 1U << (index % nbits);
		#endif
		m_pool[i] = value ? m_pool[i] | mask : m_pool[i];
	}

	bool BitsArray::Get(std::size_t index) const
	{
		const uintsys_t i = index / nbits;
		if(i > m_size)
		{
			Error("Bits Array get : index out of range");
			return false;
		}
		#ifdef AK_64BITS
			return m_pool[i] & (1ULL << (index % nbits));
		#else
			return m_pool[i] & (1U << (index % nbits));
		#endif
	}

	size_t BitsArray::GetFirstTrueBit()
	{
		for(size_t i = 0; i < m_size; i++)
		{
			if(m_pool[i] != 0)
			{
				for(size_t j = i * CHAR_BIT; j < i * CHAR_BIT + CHAR_BIT; j++)
				{
					if(Get(j))
						return j;
				}
			}
		}
		return -1;
	}
}
