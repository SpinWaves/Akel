// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/05/2022
// Updated : 24/10/2022

#ifndef __AK_KILA_COMPILER__
#define __AK_KILA_COMPILER__

#include <Akpch.h>

#include "types.h"
#include "tokens.h"

namespace Ak::Kl
{
	type_handle parse_type(class compiler_context& ctx, class tk_iterator& it);
	std::string parse_declaration_name(class compiler_context& ctx, class tk_iterator& it, bool is_function);
	void parse_token_value(class tk_iterator& it, const token_value& value);

	class Compiler
	{
		public:
			constexpr Compiler() = default;

			std::vector<uint32_t> generateSpirV(const std::string& code);
			inline std::vector<uint32_t> generateSpirVFromFile(const std::string& path) { return generateSpirV(loadFile(path)); }

			~Compiler() = default;

		private:
			std::string loadFile(const std::string& path);

			void compile_simple_statement();
			void compile_block_statement();
			void compile_for_statement();
			void compile_while_statement();
			void compile_if_statement();
			void compile_var_statement();
			void compile_break_statement();
			void compile_return_statement();
			void compile_statement();
			void compile_variable_declaration();
			
			compiler_context _ctx;
			std::vector<uint32_t> _code;
			tk_iterator _it;
	};
}

#endif // __AK_KILA_COMPILER__
