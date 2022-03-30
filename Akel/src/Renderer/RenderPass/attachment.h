// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_ATTACHMENT__
#define __AK_VK_ATTACHMENT__

#include <Akpch.h>
#include <Maths/vec3.h>

namespace Ak
{
	class Attachment
	{
		public:
			enum class type {image, depth, swapchain};

			Attachment(uint32_t binding, std::string name, type type, bool multisampled = false, VkFormat format = VK_FORMAT_R8G8B8A8_UNORM, const Maths::Vec3<float>& clearColour = Maths::Vec3<float>(0.0, 0.0, 0.0)) :
				_binding(binding),
				_name(std::move(name)),
				_type(type),
				_multisampled(multisampled),
				_format(format),
				_clearColour(clearColour) {}

			inline uint32_t getBinding() const noexcept { return _binding; }
			inline const std::string& getName() const noexcept { return _name; }
			inline type getType() const noexcept { return _type; }
			inline bool isMultisampled() const noexcept { return _multisampled; }
			inline VkFormat getFormat() const noexcept { return _format; }
			inline const Maths::Vec3<float>& getClearColour() const noexcept { return _clearColour; }

		private:
			uint32_t _binding;
			std::string _name;
			type _type;
			bool _multisampled;
			VkFormat _format;
			Maths::Vec3<float> _clearColour;
	};
}

#endif // __AK_VK_ATTACHMENT__
