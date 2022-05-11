// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 11/05/2022

#include "node.h"
#include "lexer.h"
#include "errors.h"
#include "tk_iterator.h"
#include "node_parser.h"

namespace Ak::Kl
{
	enum class operator_precedence
	{
		brackets,
		postfix,
		prefix,
		multiplication,
		addition,
		shift,
		comparison,
		equality,
		logical_and,
		logical_or,
		assignment,
		comma,
	};
    
	enum class operator_associativity
	{
		left_to_right,
		right_to_left
	};
    
	struct operator_info
	{
		node_op operation;
		operator_precedence precedence;
		operator_associativity associativity;
		int number_of_operands;
		size_t line_number;

		operator_info(node_op operation, size_t line_number) : operation(operation), line_number(line_number)
		{
			switch(operation)
			{
				case node_op::init: precedence = operator_precedence::brackets; break;
				case node_op::param:
				case node_op::index:
				case node_op::call: precedence = operator_precedence::postfix; break;
				case node_op::positive:
				case node_op::negative:
				case node_op::size:
				case node_op::lnot: precedence = operator_precedence::prefix; break;
				case node_op::mul:
				case node_op::div:
				case node_op::mod: precedence = operator_precedence::multiplication; break;
				case node_op::add:
				case node_op::sub: precedence = operator_precedence::addition; break;
				case node_op::lt:
				case node_op::gt:
				case node_op::le:
				case node_op::ge: precedence = operator_precedence::comparison; break;
				case node_op::eq:
				case node_op::ne: precedence = operator_precedence::equality; break;
				case node_op::assign:
				case node_op::add_assign:
				case node_op::sub_assign:
				case node_op::mul_assign:
				case node_op::div_assign:
				case node_op::mod_assign:
				case node_op::comma: precedence = operator_precedence::comma; break;
			}

			switch(precedence)
			{
				case operator_precedence::prefix:
				case operator_precedence::assignment: associativity = operator_associativity::right_to_left; break;

				default: associativity = operator_associativity::left_to_right; break;
			}

			switch(operation)
			{
				case node_op::init: number_of_operands = 0; break;
				case node_op::positive:
				case node_op::negative:
				case node_op::lnot:
				case node_op::size:
				case node_op::call: number_of_operands = 1; break;
				case node_op::ternary: number_of_operands = 3; break;

				default: number_of_operands = 2; break;
			}
		}
	};

	operator_info get_operator_info(Tokens token, bool prefix, size_t line_number)
	{
		switch(token)
		{
			case Tokens::add: return prefix ? operator_info(node_op::positive, line_number) : operator_info(node_op::add, line_number);
			case Tokens::sub: return prefix ? operator_info(node_op::negative, line_number) : operator_info(node_op::sub, line_number);
			case Tokens::mul: return operator_info(node_op::mul, line_number);
			case Tokens::div: return operator_info(node_op::div, line_number);
			case Tokens::mod: return operator_info(node_op::mod, line_number);
			case Tokens::assign: return operator_info(node_op::assign, line_number);
			case Tokens::add_assign: return operator_info(node_op::add_assign, line_number);
			case Tokens::sub_assign: return operator_info(node_op::sub_assign, line_number);
			case Tokens::mul_assign: return operator_info(node_op::mod_assign, line_number);
			case Tokens::div_assign: return operator_info(node_op::div_assign, line_number);
			case Tokens::mod_assign: return operator_info(node_op::mod_assign, line_number);
			case Tokens::logical_not: return operator_info(node_op::lnot, line_number);
			case Tokens::logical_and: return operator_info(node_op::land, line_number);
			case Tokens::logical_or:  return operator_info(node_op::lor, line_number);
			case Tokens::eq: return operator_info(node_op::eq, line_number);
			case Tokens::ne: return operator_info(node_op::ne, line_number);
			case Tokens::lt: return operator_info(node_op::lt, line_number);
			case Tokens::gt: return operator_info(node_op::gt, line_number);
			case Tokens::le: return operator_info(node_op::le, line_number);
			case Tokens::ge: return operator_info(node_op::ge, line_number);
			case Tokens::comma: return operator_info(node_op::comma, line_number);
			case Tokens::bracket_b: return operator_info(node_op::call, line_number);
			case Tokens::square_b: return operator_info(node_op::index, line_number);
			case Tokens::kw_size: return operator_info(node_op::size, line_number);
			case Tokens::embrace_b: return operator_info(node_op::init, line_number);

			default: unexpected_syntax_error(std::to_string(token).c_str(), line_number).expose();
		}
	}

	bool is_end_of_expression(const Token& t, bool allow_comma)
	{
		if(t.is_eof())
			return true;

		if(t.is_keyword())
		{
			switch(t.get_token())
			{
				case Tokens::bracket_e:
				case Tokens::square_e:
				case Tokens::embrace_e:
				case Tokens::colon: return true;
				case Tokens::comma: return !allow_comma;

				default: return false;
			}
		}

		return false;
	}

	inline bool is_evaluated_before(const operator_info& l, const operator_info& r)
	{
		return l.associativity == operator_associativity::left_to_right ? l.precedence <= r.precedence : l.precedence < r.precedence;
	}

	void pop_one_operator(std::stack<operator_info>& operator_stack, std::stack<node_ptr>& operand_stack, compiler_context& context, size_t line_number)
	{
		if(operand_stack.size() < operator_stack.top().number_of_operands)
			compiler_error("failed to parse an expression", line_number).expose();

		std::vector<node_ptr> operands;
		operands.resize(operator_stack.top().number_of_operands);

		if(operator_stack.top().precedence != operator_precedence::prefix)
			operator_stack.top().line_number = operand_stack.top()->get_line_number();

		for(int i = operator_stack.top().number_of_operands - 1; i >= 0; i--)
		{
			operands[i] = std::move(operand_stack.top());
			operand_stack.pop();
		}

		operand_stack.push(std::make_unique<node>(context, operator_stack.top().operation, std::move(operands), operator_stack.top().line_number));
		operator_stack.pop();
	}

	node_ptr parse_nodes_tree_impl(compiler_context& context, tk_iterator& it, bool allow_comma, bool allow_empty)
	{
		std::stack<node_ptr> operand_stack;
		std::stack<operator_info> operator_stack;

		bool expected_operand = true;

		for(; !is_end_of_expression(*it, allow_comma); ++it)
		{
			if(it->is_keyword())
			{
				operator_info oi = get_operator_info(it->get_token(), expected_operand, it->get_line_number());

				if(oi.operation == node_op::call && expected_operand)
				{
					//open round bracket is misinterpreted as a function call
					++it;
					operand_stack.push(parse_expression_tree_impl(context, it, true, false));
					if(it->has_value(Tokens::bracket_e))
					{
						expected_operand = false;
						continue;
					}
					else
						syntax_error("expected closing ')'", it->get_line_number()).expose();
				}

				if(oi.operation == node_op::init && expected_operand)
				{
					++it;
					std::vector<node_ptr> children;
					if(!it->has_value(Tokens::embrace_e))
					{
						while (true)
						{
							children.push_back(parse_nodes_tree_impl(context, it, false, false));
							if(it->has_value(Tokens::embrace_e))
							break;
							else if(it->has_value(Tokens::comma))
							++it;
							else
							syntax_error("expected ',', or closing '}'", it->get_line_number()).expose();
						}
					}
					operand_stack.push(std::make_unique<node>(context, node_op::init, std::move(children), it->get_line_number()));
					expected_operand = false;
					continue;
				}

				if((oi.precedence == operator_precedence::prefix) != expected_operand)
					unexpected_syntax_error(std::to_string(it->get_value()).c_str(), it->get_line_number()).expose();

				if(!operator_stack.empty() && is_evaluated_before(operator_stack.top(), oi))
					pop_one_operator(operator_stack, operand_stack, context, it->get_line_number());

				switch(oi.operation)
				{
					case node_op::call:
					{
						++it;
						if(!it->has_value(Tokens::bracket_e))
						{
							while(true)
							{
								node_ptr argument = parse_nodes_tree_impl(context, it, false, false);

								size_t line_number = argument->get_line_number();
								std::vector<node_ptr> argument_vector;
								argument_vector.push_back(std::move(argument));
								argument = std::make_unique<node>(context, node_op::param, std::move(argument_vector), line_number);

								operand_stack.push(std::move(argument));

								++oi.number_of_operands;

								if(it->has_value(Tokens::bracket_e))
									break;
								else if(it->has_value(Tokens::comma))
									++it;
								else
									syntax_error("expected ',' or closing ')'", it->get_line_number()).expose();
							}
						}
						break;
					}
					case node_op::index:
						++it;
						operand_stack.push(parse_nodes_tree_impl(context, it, true, false));
						if(!it->has_value(Tokens::square_e))
							syntax_error("expected closing ]'", it->get_line_number()).expose();
					break;

					default: break;
				}

				operator_stack.push(oi);
				expected_operand = (oi.precedence != operator_precedence::postfix);
			}
			else
			{
				if(!expected_operand)
					unexpected_syntax_error(std::to_string(it->get_value()).c_str(), it->get_line_number()).expose();
				if(it->is_number())
					operand_stack.push(std::make_unique<node>(context, it->get_number(), std::vector<node_ptr>(), it->get_line_number()));
				else if(it->is_string()) 
					operand_stack.push(std::make_unique<node>(context, it->get_string(), std::vector<node_ptr>(), it->get_line_number()));
				else
					operand_stack.push(std::make_unique<node>(context, it->get_identifier(), std::vector<node_ptr>(), it->get_line_number()));
				expected_operand = false;
			}
		}

		if(expected_operand)
		{
			if(allow_empty && operand_stack.empty() && operator_stack.empty())
				return node_ptr();
			syntax_error("operand expected", it->get_line_number()).expose();
		}

		while(!operator_stack.empty())
			pop_one_operator(operator_stack, operand_stack, context, it->get_line_number());

		if(operand_stack.size() != 1 || !operator_stack.empty())
			compiler_error("failed to parse an expression", it->get_line_number()).expose();

		return std::move(operand_stack.top());
	}

	node_ptr parse_nodes_tree(compiler_context& context, tk_iterator& it, type_handle type_id, bool allow_comma)
	{
		node_ptr ret = parse_nodes_tree_impl(context, it, allow_comma, type_id == type_registry::get_void_handle());
		if(ret)
			ret->check_conversion(type_id, false);
		return ret;
	}
}
