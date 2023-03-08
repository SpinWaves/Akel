// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/03/2023
// Updated : 03/03/2023

#ifndef __AK_DESCRIPTORS_LIBRARY__
#define __AK_DESCRIPTORS_LIBRARY__

#include <Akpch.h>
#include <Utils/selfInstance.h>

namespace Ak
{
	using DescSetID = uint32_t;
	constexpr DescSetID nulldescset = 0;

	class DescriptorSetLibrary : public SelfInstance<DescriptorsLibrary>
	{
		public:
			DescriptorSet

		private:
			std::unordered_map<DescSetID, std::shared_ptr<DescriptorSet>> _cache;
			DescSetID _current_id = 1;
	};
}

#endif
