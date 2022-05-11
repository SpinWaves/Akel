// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 11/05/2022

#include "compiler_context.h"

const identifier_info* compiler_context::find(const std::string& name) const
{
	if(_locals && const identifier_info* ret = _locals->find(name))
		return ret;
	if(const identifier_info* ret = _functions.find(name))
		return ret;
	return _globals.find(name);
}

void compiler_context::enter_function()
{
	unique_ptr_w<param_lookup> params = create_unique_ptr_w<param_lookup>();
	_params = params.get();
	_locals = std::move(params);
}

void compiler_context::leave_scope()
{
	if(_params == _locals.get())
		_params = nullptr;
	_locals = _locals->detach_parent();
}
