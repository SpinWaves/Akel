// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/10/2022
// Updated : 27/01/2023

#ifndef __AK_KILA_COMPILER__
#define __AK_KILA_COMPILER__

#include <Akpch.h>

#include "tokens.h"
#include "token_iterator.h"
#include <Core/profile.h>

namespace Ak::Kl
{
	class AK_API Compiler
	{
		public:
			Compiler() = default;

			std::vector<uint32_t> generateSpirV(const std::string& code);
			inline std::vector<uint32_t> generateSpirVFromFile(const std::string& path) { return generateSpirV(loadFile(path)); }

			~Compiler() = default;

		private:
			std::string loadFile(const std::string& path);
			std::vector<uint32_t> _code;
			tk_iterator _it;
	};
}

#endif // __AK_KILA_COMPILER__