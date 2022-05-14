// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 14/05/2022

#include "node.h"
#include "errors.h"
#include <Utils/utils.h>

namespace Ak::Kl
{
	Node::Node(node_op op, std::vector<node_ptr> children, size_t line_number) : _op(std::move(op)), _children(std::move(children)), _line_number(line_number)
	{    
		switch(op)
		{
			case node_op::param: break;
			case node_op::positive: break;
			case node_op::negative: break;
			case node_op::lnot: break;
			case node_op::len: break;
			case node_op::add: break;
			case node_op::sub: break;
			case node_op::mul: break;
			case node_op::div: break;
			case node_op::mod: break;
			case node_op::land: break;
			case node_op::lor: break;
			case node_op::eq: break;
			case node_op::ne: break;
			case node_op::lt: break;
			case node_op::gt: break;
			case node_op::le: break;
			case node_op::ge: break;
			case node_op::assign: break;
			case node_op::add_assign: break;
			case node_op::sub_assign: break;
			case node_op::mul_assign: break;
			case node_op::div_assign: break;
			case node_op::mod_assign: break;
			case node_op::comma: break;
			case node_op::index: break;
			case node_op::call: break;
			case node_op::init: break;
		}
	}
}
