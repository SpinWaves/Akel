// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/05/2022
// Updated : 11/05/2022

#ifndef __AK_KILA_NODE__
#define __AK_KILA_NODE__

#include <Akpch.h>
#include "tokens.h"
#include "compiler_context.h"
#include <Core/core.h>

namespace Ak::Kl
{
	enum class node_op
	{
		param,

		positive,
		negative,

		add,
		sub,
		mul,
		div,
		mod,
		
		assign,
		add_assign,
		sub_assign,
		mul_assign,
		div_assign,
		mod_assign,
		
		eq,
		ne,
		lt,
		gt,
		le,
		ge,

		comma,
		
		land,
		lor,
		lnot,    

		call,

		//import
	};

	struct Node;
	using node_ptr = unique_ptr_w<Node>;
	using node_value = std::variant<node_op, double, long long, identifier>;

	struct Node
	{
		Node(compiler_context& context, node_value value, std::vector<node_ptr> children, size_t line_number);

		inline const node_value& get_value() const { return _value; }

		inline bool is_node_operation() const { return std::holds_alternative<node_operation>(_value); }
		inline bool is_identifier() const { return std::holds_alternative<identifier>(_value); }
		inline bool is_floating_point() const { return std::holds_alternative<double>(_value); }
		inline bool is_integer() const { return std::holds_alternative<long long>(_value); }

		inline node_operation get_node_operation() const { return std::get<node_operation>(_value); }
		inline std::string_view get_identifier() const { return std::get<identifier>(_value).name; }
		inline double get_floating_point() const { return std::get<double>(_value); }
		inline long long get_integer() const { return std::get<long long>(_value); }
		inline const std::vector<node_ptr>& get_children() const { return _children; }
		inline type_handle get_type_id() const { return _type_id; }

		inline size_t get_line_number() const { return _line_number; }

		void check_conversion(type_handle type_id, bool lvalue) const;

		private:
			node_value _value;
			std::vector<node_ptr> _children;
			type_handle _type_id;
			bool _lvalue;
			size_t _line_number;
	};
}

#endif // __AK_KILA_NODE__
