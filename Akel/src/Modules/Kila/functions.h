// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 22/10/2022

#ifndef __AK_KILA_FUNCTIONS__
#define __AK_KILA_FUNCTIONS__

#include <Akpch.h>
#include "tokens.h"
#include "types.h"

namespace Ak::Kl
{
	struct function_declaration
	{
		std::vector<std::string> params;
		std::string name;
		type_handle type_id;
	};

	function_declaration parse_function_declaration(class compiler_context& ctx, class tk_iterator& it);

	class function_body
	{
		public:
			function_body(class compiler_context& ctx, class tk_iterator& it);
			function_body(function_body&& orig) noexcept;

			inline const function_declaration& get_decl() const { return _decl; }

			void compile(class compiler_context& ctx);

		private:
			function_declaration _decl;
			std::deque<Token> _tokens;
			size_t _index;
	};
}

#endif // __AK_KILA_FUNCTIONS__
