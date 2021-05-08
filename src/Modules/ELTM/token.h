// This file is a part of AtlasEngine
// CREATED : 05/05/2021
// UPDATED : 08/05/2021

#ifndef __ELTM_TOKEN__
#define __ELTM_TOKEN__

#include <AEpch.h>

namespace AE
{
	enum struct eltm_token
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
		assign
	};


	const std::map<std::string, eltm_token> keyword_token
	{
		{"set", eltm_token::kw_set},
		{"=", eltm_token::assign},
		{"get", eltm_token::kw_get},

		{"import", eltm_token::kw_import},

		{"begin", eltm_token::kw_begin},
		{"end", eltm_token::kw_end},

		{"module", eltm_token::kw_module},

		{"//", eltm_token::basic_comment},
		{"/*", eltm_token::begin_long_comment},
		{"*/", eltm_token::end_long_comment}
	};

	class Token
	{
		public:
			Token(std::variant<eltm_token, std::string> value, size_t line, size_t index);

			bool isString();
			bool isKeyword();
			
			std::string getString();
			eltm_token getReservedToken();
			size_t getLine();
			size_t getIndex();

		private:
			std::variant<eltm_token, std::string> _value;
			size_t _line;
			size_t _index;
	};
}

#endif // __ELTM_TOKEN__

