// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/02/2023
// Updated : 06/02/2023

#include <Utils/mStrings.h>

namespace Ak
{
	mString::mString()
	{
	}

	mString::mString(const char* str)
	{
	}

	mString::mString(const mString& str)
	{
	}

	mString::mString(mString&& str)
	{
	}

	mString& mString::append(mString str)
	{
		return *this;
	}
	mString& mString::append(mString str, size_t subpos, size_t sublen)
	{
		return *this;
	}
	mString& mString::append(const char* str)
	{
		return *this;
	}

	char mString::pop_back()
	{
		return 0;
	}
}