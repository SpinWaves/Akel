// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/05/2022
// Updated : 19/10/2022

#include "compiler_context.h"
#include <Core/core.h>

namespace Ak::Kl
{
	Context::Context(std::string name, uint32_t kila_version)
	{
		meta_data_ptr = create_shared_ptr_w();
		meta_data_ptr->name = std::move(name);
		meta_data_ptr->kila_version = kila_version;
	}
}
