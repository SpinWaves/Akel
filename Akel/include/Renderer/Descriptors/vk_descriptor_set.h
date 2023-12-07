// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 06/11/2023

#ifndef __AK_VK_DESCRIPTOR_SET__
#define __AK_VK_DESCRIPTOR_SET__

#include <Akpch.h>

namespace Ak
{
	class DescriptorSet
	{
		public:
			void init(class RendererComponent* renderer, class DescriptorSetLayout* layout, class DescriptorPool* pool, int32_t index);

			void writeDescriptor(int binding, const class UBO& ubo) noexcept;
			void writeDescriptor(int binding, VkImageView view, VkSampler sampler) noexcept;

			inline bool isInit() noexcept { return _pool != nullptr && _layout != nullptr && _renderer != nullptr; }
			inline int32_t getIndex() const noexcept { return _index; }

			DescriptorSet duplicate() const;

			void destroy() noexcept;

			const VkDescriptorSet& operator()() const noexcept;
			const VkDescriptorSet& get() const noexcept;

		private:
			std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT> _desc_set;
			class DescriptorPool* _pool = nullptr;
			class DescriptorSetLayout* _layout = nullptr;
			class RendererComponent* _renderer = nullptr;
			int32_t _index = -1;
    };
}

#endif // __AK_VK_DESCRIPTOR_SET__
