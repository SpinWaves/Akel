// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 15/05/2022

#ifndef __AK_KILA_COMPILER__
#define __AK_KILA_COMPILER__

#include <Akpch.h>

#include "types.h"
#include "tokens.h"

namespace Ak::Kl
{
	type_handle parse_type(class compiler_context& ctx, class tk_iterator& it);
	std::string parse_declaration_name(class compiler_context& ctx, class tk_iterator& it);
	void parse_token_value(class compiler_context& ctx, class tk_iterator& it, const token_value& value);
}

#endif // __AK_KILA_COMPILER__
