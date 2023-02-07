// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/10/2022
// Updated : 03/11/2022

#include <Modules/Kila/spirv_part.h>

namespace Ak::Kl
{
	void SpvPart::addraw(std::string_view str)
	{
		for(uint32_t i = 0; i < countWord(str); i++)
		{
			uint32_t code_point = 0;
			for(uint32_t j = 0; j < 4; j++)
			{
				uint32_t pos = i * 4 + j;
				if(pos < str.size())
					code_point |= uint32_t(str[pos]) << (j * 8);
			}
			addraw(code_point);
		}
	}
}
