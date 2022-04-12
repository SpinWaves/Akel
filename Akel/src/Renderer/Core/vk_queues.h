// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 12/04/2022

#ifndef __AK_VK_QUEUES__
#define __AK_VK_QUEUES__

#include <Akpch.h>

namespace Ak
{
	class Queues
	{
		public:
			struct QueueFamilyIndices
			{
				std::optional<uint32_t> graphicsFamily;
				std::optional<uint32_t> presentFamily;

				inline bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
			};

			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

			inline VkQueue& getGraphic() const noexcept { return _graphicsQueue; }
			inline VkQueue& getPresent() const noexcept { return _presentQueue; }

		private:
			VkQueue _graphicsQueue;
			VkQueue _presentQueue;
	};
}

#endif // __AK_VK_QUEUES__
