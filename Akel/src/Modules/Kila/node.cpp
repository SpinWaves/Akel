// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 26/10/2022

#include "node.h"
#include "errors.h"
#include <Utils/utils.h>

namespace Ak::Kl
{
	bool is_convertible(type_handle type_from, bool lvalue_from, type_handle type_to, bool lvalue_to)
	{
		if(type_to == type_registry::get_void_handle())
			return true;
		if(lvalue_to)
			return lvalue_from && type_from == type_to;
		if(type_from == type_to)
			return true;
		if(const init_list_type* ilt = std::get_if<init_list_type>(type_from))
		{
			if(lvalue_to)
				return false;
			if(type_to == type_registry::get_void_handle())
				return true;

			return std::visit(overloaded
			{
				[&](const matrix_type& at)
				{
					for(type_handle it : ilt->inner_type_id)
						if(it != at.inner_type_id)
							return false;
					return true;
				},
				[&](const type&) { return false; }
			}, *type_to);
		}
		return false;
	}

	void Node::check_conversion(type_handle type_id, bool lvalue) const
	{
		if(!is_convertible(_type_id, _lvalue, type_id, lvalue))
			wrong_type_error(std::to_string(_type_id).c_str(), std::to_string(type_id).c_str(), lvalue, _line_number).expose();
	}

	Node::Node(compiler_context& context, node_value value, std::vector<node_ptr> children, size_t line_number) : _value(std::move(value)), _children(std::move(children)), _line_number(line_number)
	{
		const type_handle void_handle = type_registry::get_void_handle();
		const type_handle number_handle = type_registry::get_number_handle();
		const type_handle boolean_handle = type_registry::get_boolean_handle();

		std::visit(overloaded
		{
			[&](double value)
			{
				_type_id = number_handle;
				_lvalue = false;
			},
			[&](bool value)
			{
				_type_id = boolean_handle;
				_lvalue = false;
			},
			[&](const identifier& value)
			{
				if(const identifier_info* info = context.find(value.name))
				{
					_type_id = info->type_id();
					_lvalue = (info->get_scope() != identifier_scope::function);
				}
				else
					undeclared_error(value.name.c_str(), _line_number).expose();
			},
			[&](node_op value)
			{
				switch(value)
				{
					case node_op::param:
						_type_id = _children[0]->_type_id;
						_lvalue = false;
					break;
					case node_op::positive:
					case node_op::negative:
					case node_op::lnot:
						_type_id = boolean_handle;
						_lvalue = false;
						_children[0]->check_conversion(number_handle, false);
					break;
					case node_op::add:
					case node_op::sub:
					case node_op::mul:
					case node_op::div:
					case node_op::mod:
						_lvalue = false;
						if(_children[0]->is_number() || _children[1]->is_number())
						{
							_type_id = number_handle;
							_children[0]->check_conversion(number_handle, false);
							_children[1]->check_conversion(number_handle, false);
						}
						else
							semantic_error(std::string(std::to_string(!_children[1]->is_number() ? _children[0]->get_type_id() : _children[1]->get_type_id()) + " is not a number").c_str(), _line_number).expose();
					break;
					case node_op::land:
					case node_op::lor:
					case node_op::eq:
					case node_op::ne:
					case node_op::lt:
					case node_op::gt:
					case node_op::le:
					case node_op::ge:
						_type_id = boolean_handle;
						_lvalue = false;
						if(_children[0]->is_number() || !_children[1]->is_number())
						{
							_children[0]->check_conversion(number_handle, false);
							_children[1]->check_conversion(number_handle, false);
						}
						else
						{
							_children[0]->check_conversion(boolean_handle, false);
							_children[1]->check_conversion(boolean_handle, false);
						}
					break;
					case node_op::assign:
						_type_id = _children[0]->get_type_id();
						_lvalue = true;
						_children[0]->check_conversion(_type_id, true);
						_children[1]->check_conversion(_type_id, false);
					break;
					case node_op::add_assign:
					case node_op::sub_assign:
					case node_op::mul_assign:
					case node_op::div_assign:
					case node_op::mod_assign:
						_type_id = number_handle;
						_lvalue = true;
						if(_children[0]->is_number() || _children[1]->is_number())
						{
							_children[0]->check_conversion(number_handle, false);
							_children[1]->check_conversion(number_handle, false);
						}
					break;
					case node_op::comma:
						for(int i = 0; i < int(_children.size()) - 1; i++)
							_children[i]->check_conversion(void_handle, false);
						_type_id = _children.back()->get_type_id();
						_lvalue = _children.back()->is_lvalue();
					break;
					case node_op::index:
						_lvalue = _children[0]->is_lvalue();
						if(const matrix_type* at = std::get_if<matrix_type>(_children[0]->get_type_id()))
							_type_id = at->inner_type_id;
						else
							semantic_error(std::string(to_string(_children[0]->_type_id) + " is not indexable").c_str(), _line_number).expose();
					break;
					case node_op::call:
					{
						if(const function_type* ft = std::get_if<function_type>(_children[0]->get_type_id()))
						{
							_type_id = ft->return_type_id;
							_lvalue = false;
							if(ft->param_type_id.size() + 1 != _children.size())
								semantic_error(std::string("wrong number of arguments. Expected " + std::to_string(ft->param_type_id.size()) + ", given " + std::to_string(_children.size() - 1)).c_str(), _line_number).expose();
							for(size_t i = 0; i < ft->param_type_id.size(); i++)
								_children[i + 1]->check_conversion(ft->param_type_id[i].type_id, false);
						}
						else
						{
							if(_children[0]->is_identifier())
								semantic_error(std::string(std::string(_children[0]->get_identifier()) + " (" + to_string(_children[0]->_type_id) + ") is not callable").c_str(), _line_number).expose();
							semantic_error(std::string(to_string(_children[0]->_type_id) + " is not callable").c_str(), _line_number).expose();
						}
						break;
					}
					case node_op::init:
					{
						init_list_type ilt;
						ilt.inner_type_id.reserve(_children.size());

						for(const node_ptr& child : _children)
							ilt.inner_type_id.push_back(child->get_type_id());

						_type_id = context.get_handle(ilt);
						_lvalue = false;
						break;
					}
				}
			}
		}, _value);
	}
}
