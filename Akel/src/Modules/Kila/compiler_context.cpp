// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 21/10/2022

#include "compiler_context.h"
#include <Core/core.h>

namespace Ak::Kl
{
	const identifier_info* compiler_context::find(const std::string& name) const
	{
		identifier_info* ret = const_cast<identifier_info*>(_locals->find(name));
		if(_locals && ret)
			return ret;
		ret = const_cast<identifier_info*>(_functions.find(name));
		if(ret)
			return ret;
		return _globals.find(name);
	}

	void compiler_context::leave_scope()
	{
		if(_params == _locals.get())
			_params = nullptr;
		_locals = _locals->detach_parent();
	}
}
