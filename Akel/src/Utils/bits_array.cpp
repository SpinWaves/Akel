// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2022
// Updated : 12/11/2022

#include <Utils/bits_array.h>
#include <Core/log.h>

namespace Ak
{
	void BitsArray::init(size_t bits_n)
	{
		_size = (nbits + bits_n - 1) / nbits;
		_pool.reset(new uintsys_t[_size]);
		std::memset(_pool.get(), 0, _size);
	}

	void BitsArray::resetBits(bool value)
	{
		std::memset(_pool.get(), value ? 255 : 0, _size);
	}

	void BitsArray::set(size_t index, bool value)
	{
		const uintsys_t i = index / nbits;
		if(i > _size)
		{
			Core::log::report(ERROR, "Bits Array set : index out of range");
			return;
		}
#ifdef AK_64BITS
		const uintsys_t mask = 1ULL << (index % nbits);
#else
		const uintsys_t mask = 1U << (index % nbits);
#endif
		_pool[i] = value ? _pool[i] | mask : _pool[i];
	}

	bool BitsArray::get(size_t index) const
	{
		const uintsys_t i = index / nbits;
		if(i > _size)
		{
			Core::log::report(ERROR, "Bits Array get : index out of range");
			return false;
		}
#ifdef AK_64BITS
		return _pool[i] & (1ULL << (index % nbits));
#else
		return _pool[i] & (1U << (index % nbits));
#endif
	}

	size_t BitsArray::getFirstTrueBit()
	{
		for(size_t i = 0; i < _size; i++)
		{
			if(_pool[i] != 0)
			{
				for(size_t j = i * CHAR_BIT; j < i * CHAR_BIT + CHAR_BIT; j++)
				{
					if(get(j))
						return j;
				}
			}
		}
		return -1;
	}
}
