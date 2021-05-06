// This file is a part of AtlasEngine
// CREATED : 06/05/2021
// UPDATED : 06/05/2021

#ifndef __MTML_TOKEN__
#define __MTML_TOKEN__

#include <AEpch.h>

namespace AE
{
	enum struct mtml_token
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

	class Token
	{
		public:
			Token(std::variant<mtml_token, std::string> value, size_t line, size_t index);

			bool isString();
			bool isKeyword();
			
			std::string getString();
			mtml_token getReservedToken();
			size_t getLine();
			size_t getIndex();

		private:
			std::variant<mtml_token, std::string> _value;
			size_t _line;
			size_t _index;
	};

	Token tokenize(const char* file);
}

#endif // __MTML_TOKEN__

