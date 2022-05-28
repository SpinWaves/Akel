// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 28/05/2022

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

			void findQueueFamilies(VkPhysicalDevice device);

			inline VkQueue& getGraphic() noexcept { return _graphicsQueue; }
			inline VkQueue& getPresent() noexcept { return _presentQueue; }
			inline QueueFamilyIndices getFamilies() noexcept { return _families; }

		private:
			VkQueue _graphicsQueue;
			VkQueue _presentQueue;
			QueueFamilyIndices _families;
	};
}

#endif // __AK_VK_QUEUES__
