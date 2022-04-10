// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 05/04/2022

#ifndef __AK_VK_SHADER__
#define __AK_VK_SHADER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class fString;

	class Shader
	{
		public:
			enum class type { vertex, fragment }; // TODO : add more shaders types support

			Shader(const fString path, type t);

			void generate();
			inline void destroy()
			{
				static_assert(_shader != VK_NULL_HANDLE, "trying to destroy an uninit shader");
				vkDestroyShaderModule(Render_Core::get().getDevice()->get(), _shader, nullptr);
			}
 
			inline const fString& getName() const { return _name; }
			inline const VkShaderModule& getShaderModule() const noexcept { return _shader; }
			inline const type getType() const noexcept { return _type; }

			~Shader() = default;

		private:
			VkShaderModule _shader = VK_NULL_HANDLE;
			const fString _name;
			type _type;
	};
}

#endif // __AK_VK_SHADER__
