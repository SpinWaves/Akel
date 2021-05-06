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
}

#endif // __MTML_TOKEN__

