// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_SUBPASS__
#define __AK_VK_SUBPASS__

#include <Apch.h>

namespace Ak
{
	class SubpassType
	{
		public:
			SubpassType(uint32_t binding, std::vector<uint32_t> attachmentBindings) : _binding(binding), _attachmentBindings(std::move(attachmentBindings)) {}

			inline uint32_t getBinding() const noexcept { return _binding; }
			inline const std::vector<uint32_t>& getAttachmentBindings() const noexcept { return _attachmentBindings; }

		private:
			uint32_t _binding;
			std::vector<uint32_t> _attachmentBindings;
	};
}

#endif // __AK_VK_SUBPASS__
