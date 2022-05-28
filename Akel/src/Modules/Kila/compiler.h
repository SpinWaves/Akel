// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 16/05/2022

#ifndef __AK_KILA_COMPILER__
#define __AK_KILA_COMPILER__

#include <Akpch.h>

#include "types.h"
#include "tokens.h"

namespace Ak::Kl
{
	type_handle parse_type(class compiler_context& ctx, class tk_iterator& it);
	std::string parse_declaration_name(class compiler_context& ctx, class tk_iterator& it);
	void parse_token_value(class tk_iterator& it, const token_value& value);

	class Compiler
	{
		public:
			constexpr Compiler() = default;

			std::vector<uint32_t> generateSpirV(std::string code);
			inline std::vector<uint32_t> generateSpirVFromFile(const std::string& path) { return generateSpirV(loadFile(path)); }

			~Compiler() = default;

		private:
			std::string loadFile(const std::string& path);
	};
}

#endif // __AK_KILA_COMPILER__
