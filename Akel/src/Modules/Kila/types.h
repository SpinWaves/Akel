// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/05/2022
// Updated : 10/05/2022

#ifndef __AK_KILA_TYPES__
#define __AK_KILA_TYPES__

#include <Akpch.h>

namespace Ak::Kl
{
	enum class simple_type
	{
		nothing,
		floating,
		integer
	};

	struct function_type;

	using type = std::variant<simple_type, function_type>;
	using type_handle = const type*;

	struct matrix_type
	{
		type_handle inner_type_id;
	};

	struct init_list_type
	{
		std::vector<type_handle> inner_type_id;
	};

	struct function_type
	{
		struct param
		{
			type_handle type_id;
		};
		type_handle return_type_id;
		std::vector<param> param_type_id;
	};

	class type_registry
	{
		public:
			type_registry() = default;

			type_handle get_handle(const type& t);

			inline static type_handle get_void_handle() { return &void_type; }
			inline static type_handle get_floating_handle() { return &floating_type; }
			inline static type_handle get_integer_handle() { return &integer_type; }

		private:
			struct types_less
			{
				bool operator()(const type& t1, const type& t2) const;
			};
			std::set<type, types_less> _types;

			static type void_type;
			static type floating_type;
			static type integer_type;
	};

	namespace std { std::string to_string(type_handle t); }
}

#endif // __AK_KILA_TYPES__
