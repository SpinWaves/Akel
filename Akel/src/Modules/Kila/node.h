// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/05/2022
// Updated : 14/05/2022

#ifndef __AK_KILA_NODE__
#define __AK_KILA_NODE__

#include <Akpch.h>
#include "tokens.h"
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
		index,
		len,
		init,

		//import
	};

	struct Node;
	using node_ptr = Unique_ptr<Node>;

	struct Node
	{
		Node(node_op op, std::vector<node_ptr> children, size_t line_number);

		inline const node_op& get_op() const noexcept { return _op; }
		inline const std::vector<node_ptr>& get_children() const { return _children; }

		inline size_t get_line_number() const { return _line_number; }

		private:
			node_op _op;
			std::vector<node_ptr> _children;
			size_t _line_number;
	};
}

#endif // __AK_KILA_NODE__
