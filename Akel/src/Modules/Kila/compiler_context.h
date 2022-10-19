// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/05/2022
// Updated : 19/10/2022

#ifndef __AK_KILA_COMPILER_CONTEXT__
#define __AK_KILA_COMPILER_CONTEXT__

#include <Akpch.h>

#include "types.h"

namespace Ak::Kl
{
	using ContextPtr = std::shared_ptr<class Context>;

	class Context
	{
		public:
			struct MetaData;

			Context() = default;
			inline Context(std::shared_ptr<const MetaData> metaData) : meta_data_ptr(std::move(metaData)) {}
			Context(std::string name, uint32_t kila_version);
			Context(const Context&) = delete;
			Context(Context&&) noexcept = default;
			Context& operator=(const Context&) = delete;
			Context& operator=(Context&&) noexcept = default;
			~Context() = default;

			struct MetaData
			{
				std::string author;
				std::string name;
				uint32_t kila_version;
			};
			
			std::shared_ptr<const MetaData> meta_data_ptr;
	};
}

#endif // __AK_KILA_COMPILER_CONTEXT__
