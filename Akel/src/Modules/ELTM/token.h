// This file is a part of Akel
// CREATED : 05/05/2021
// UPDATED : 13/07/2021

#ifndef __AK_ELTM_TOKEN__
#define __AK_ELTM_TOKEN__

#include <Akpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>
#include <Core/profile.h>

namespace Ak
{
	enum class eltm_token
	{
		kw_set,
		kw_import,

		kw_begin,
		kw_end,
		
		kw_module,			// "kw_" are keywords

		basic_comment,
		begin_long_comment,
		end_long_comment,

		kw_get,
		assign,

		begin_long_text,
		end_long_text,

		#ifdef AK_ELTM_VERSION_1_1
			
		#endif

		error
	};

	class Token
	{
		public:
			Token(std::variant<eltm_token, std::string> value);

			static inline duets_array<eltm_token, std::string> keyword_token
			{
				{eltm_token::kw_set, "set"},
				{eltm_token::kw_get, "get"},
				{eltm_token::assign, "="},

				{eltm_token::kw_import, "import"},

				{eltm_token::kw_begin, "begin"},
				{eltm_token::kw_end, "end"},

				{eltm_token::kw_module, "module"},

				{eltm_token::basic_comment, "//"},
				{eltm_token::begin_long_comment, "/*"},
				{eltm_token::end_long_comment, "*/"},
				{eltm_token::begin_long_text, "("},
				{eltm_token::end_long_text, ")"}
			};

			static inline duets_array<eltm_token, std::string> mixable_keywords_token
			{
				{eltm_token::kw_get, "get"},
				{eltm_token::assign, "="},
				{eltm_token::basic_comment, "//"},
				{eltm_token::begin_long_comment, "/*"},
				{eltm_token::end_long_comment, "*/"},
				{eltm_token::begin_long_text, "("},
				{eltm_token::end_long_text, ")"}
			};

			bool isString();
			bool isKeyword();
			
			std::string getString(std::string file, std::string caller, size_t line)
			{
				if(isString())
					return std::get<std::string>(_value);
				if(!_activateKw)
					return keyword_token[std::get<eltm_token>(_value)];

				ELTMerrors error = context_error("token : this token is not a string", file, caller, line);
				std::cout << red << error.what() << def << std::endl;
				return "error";
			}
			eltm_token getReservedToken(std::string file, std::string caller, size_t line)
			{
				if(isKeyword())
					return std::get<eltm_token>(_value);
				ELTMerrors func_error = context_error("token : this token is not a reserved token", file, caller, line);
				std::cout << red << func_error.what() << def << std::endl;
				return eltm_token::error;
			}

			static bool isKwActivate();
			static void activateKw(bool enable = true);
			
		private:
			std::variant<eltm_token, std::string> _value;

			inline static bool _activateKw = true;
	};

	#undef getString
	#define getString() getString(__FILE__, AK_FUNC_SIG, __LINE__)
	#undef getReservedToken
	#define getReservedToken() getReservedToken(__FILE__, AK_FUNC_SIG, __LINE__)
}

#endif // __AK_ELTM_TOKEN__

