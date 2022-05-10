// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/05/2022
// Updated : 10/05/2022

#ifndef __AK_KILA_COMPILER_CONTEXT__
#define __AK_KILA_COMPILER_CONTEXT__

#include <Akpch.h>

#include "types.h"

namespace Ak::Kl
{
	enum class identifier_scope
	{
		global_variable,
		local_variable,
		function
	};

	class identifier_info
	{
		public:
			identifier_info(type_handle type_id, size_t index, identifier_scope scope);

			inline type_handle type_id() const noexcept { return _type_id; }
			inline size_t index() const noexcept { return _index; }
			inline identifier_scope get_scope() const { return _scope; }

		private:
			type_handle _type_id;
			size_t _index;
			identifier_scope _scope;
	};
}

#endif // __AK_KILA_COMPILER_CONTEXT__
