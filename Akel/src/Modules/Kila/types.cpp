// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 11/05/2022

#include "types.h"

namespace Ak::Kl
{
	bool type_registry::types_less::operator()(const type& t1, const type& t2) const
	{
		const size_t idx1 = t1.index();
		const size_t idx2 = t2.index();

		if(idx1 != idx2)
			return idx1 < idx2;

		switch(idx1)
		{
			case 0: return std::get<0>(t1) < std::get<0>(t2);
			case 1: return std::get<1>(t1).inner_type_id < std::get<1>(t2).inner_type_id;
			case 2:
			{
				const function_type& ft1 = std::get<2>(t1);
				const function_type& ft2 = std::get<2>(t2);

				if(ft1.return_type_id != ft2.return_type_id)
					return ft1.return_type_id < ft2.return_type_id;

				if(ft1.param_type_id.size() != ft2.param_type_id.size())
					return ft1.param_type_id.size() < ft2.param_type_id.size();

				for(size_t i = 0; i < ft1.param_type_id.size(); ++i)
				{
					if(ft1.param_type_id[i].type_id != ft2.param_type_id[i].type_id)
						return ft1.param_type_id[i].type_id < ft2.param_type_id[i].type_id;
					if(ft1.param_type_id[i].by_ref != ft2.param_type_id[i].by_ref)
						return ft2.param_type_id[i].by_ref;
				}

				return false;
			}
			case 3: 
			{
				const init_list_type& ilt1 = std::get<3>(t1);
				const init_list_type& ilt2 = std::get<3>(t2);

				if(ilt1.inner_type_id.size() != ilt2.inner_type_id.size())
					return ilt1.inner_type_id.size() < ilt2.inner_type_id.size();

				for(size_t i = 0; i < ilt1.inner_type_id.size(); ++i)
					if(ilt1.inner_type_id[i] != ilt2.inner_type_id[i])
					return ilt1.inner_type_id[i] < ilt2.inner_type_id[i];
			}
		}

		return false;
	}

	type_handle type_registry::get_handle(const type& t)
	{
		return std::visit(overloaded{
			[](simple_type t)
			{
				switch(t)
				{
					case simple_type::nothing: return type_registry::get_void_handle();
					case simple_type::floating_type:  return type_registry::get_floating_handle();
					case simple_type::integer:  return type_registry::get_integer_handle();
				}
			},
			[this](const auto& t) { return &(*(_types.insert(t).first)); }
		}, t);
	}

	namespace std
	{
		std::string to_string(type_handle t)
		{
			return std::visit(overloaded{
				[](simple_type st)
				{
					switch(st)
					{
						case simple_type::nothing: return std::string("void");
						case simple_type::floating_type:  return std::string("floating");
						case simple_type::integer: return std::string("integer");
					}
				},
				[](const matrix_type& at)
				{
					std::string ret = to_string(at.inner_type_id);
					ret += "[]";
					return ret;
				},
				[](const function_type& ft)
				{
					std::string ret = to_string(ft.return_type_id) + "(";
					const char* separator = "";
					for(const function_type::param& p: ft.param_type_id)
					{
						ret += separator + std::string("arg : ") + to_string(p.type_id);
						separator = ", ";
					}
					ret += ")";
					return ret;
				},
				[](const init_list_type& ilt)
				{
					std::string ret = "{ ";
					const char* separator = "";
					for(type_handle it : ilt.inner_type_id)
					{
						ret += separator + to_string(it);
						separator = ", ";
					}
					ret += "} ";
					return ret;
				},
			}, *t);
		}
	}
}
