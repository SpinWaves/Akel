// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 23/05/2021

#ifndef __ELTM_TOKEN__
#define __ELTM_TOKEN__

#include <AEpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>

namespace AE
{
	enum eltm_token
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
		
		error
	};

	class Token
	{
		public:
			Token(std::variant<eltm_token, std::string> value);

			static inline duets_array<eltm_token, std::string> keyword_token
			{
				{kw_set, "set"},
				{kw_get, "get"},
				{assign, "="},

				{kw_import, "import"},

				{kw_begin, "begin"},
				{kw_end, "end"},

				{kw_module, "module"},

				{basic_comment, "//"},
				{begin_long_comment, "/*"},
				{end_long_comment, "*/"},
				{begin_long_text, "("},
				{end_long_text, ")"}
			};

			bool isString();
			bool isKeyword();
			
			std::string getString(std::string file, std::string caller, size_t line)
			{
				if(isString())
					return std::get<std::string>(_value);

				// Comment management
				switch(std::get<eltm_token>(_value))
				{
					case basic_comment: return "___ELTM_TOKEN_COMMENT_BASIC_CODE___";
					case begin_long_comment: return "___ELTM_TOKEN_COMMENT_LONG_BEGIN_CODE___";
					case end_long_comment: return "___ELTM_TOKEN_COMMENT_LONG_END_CODE___";

					// Long text management
					case begin_long_text: return "___ELTM_TOKEN_LONG_TEXT_BEGIN_CODE___";
					case end_long_text: return "___ELTM_TOKEN_LONG_TEXT_END_CODE___";

					default: break;
				}

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
				return error;
			}

			static bool isKwActivate();
			static void activateKw(bool enable = true);
			
		private:
			std::variant<eltm_token, std::string> _value;

			inline static bool _activateKw = true;
	};

	#undef getString
	#define getString() getString(__FILE__, __FUNCTION__, __LINE__)
	#undef getReservedToken
	#define getReservedToken() getReservedToken(__FILE__, __FUNCTION__, __LINE__)
}

#endif // __ELTM_TOKEN__

