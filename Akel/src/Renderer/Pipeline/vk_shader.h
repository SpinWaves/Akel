// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 16/09/2022

#ifndef __AK_VK_SHADER__
#define __AK_VK_SHADER__

#include <Akpch.h>
#include <Utils/Containers/duetsArray.h>
#include <Renderer/Descriptors/vk_descriptor_set_layout.h>

namespace Ak
{
	class fString;

	class Shader
	{
		public:
			class Uniform
			{
				public:
					Uniform(int32_t binding = -1, int32_t set = -1, int32_t offset = -1, int32_t size = -1, VkShaderStageFlags stageFlags = 0) :
						_binding(binding),
						_set(set),
						_offset(offset),
						_size(size),
						_stageFlags(stageFlags)
					{}

					inline int32_t getBinding() const noexcept { return _binding; }
					inline int32_t getOffset() const noexcept { return _offset; }
					inline int32_t getSize() const noexcept { return _size; }
					inline int32_t getSet() const noexcept { return _set; }
					inline VkShaderStageFlags getStageFlags() const noexcept { return _stageFlags; }

					inline bool operator==(const Uniform &rhs) const
					{
						return  _binding == rhs._binding &&
								_offset == rhs._offset &&
								_size == rhs._size &&
								_set == rhs._set && 
								_stageFlags == rhs._stageFlags;
					}

					inline bool operator!=(const Uniform &rhs) const { return !operator==(rhs); }

				private:
					VkShaderStageFlags _stageFlags;
					int32_t _binding;
					int32_t _set;
					int32_t _offset;
					int32_t _size;
			};

			class VertexInput
			{
				public:
					VertexInput(std::vector<VkVertexInputBindingDescription> bindings, std::vector<VkVertexInputAttributeDescription> attributes) : _bindings(std::move(bindings)), _attributes(std::move(attributes)) {}

					const std::vector<VkVertexInputBindingDescription>& getBindingDescriptions() const { return _bindings; }
					const std::vector<VkVertexInputAttributeDescription>& getAttributeDescriptions() const { return _attributes; }

					inline bool operator<(const VertexInput& other) const { return _bindings.front().binding < other._bindings.front().binding; }

				private:
					std::vector<VkVertexInputBindingDescription> _bindings;
					std::vector<VkVertexInputAttributeDescription> _attributes;
			};

			Shader(const std::vector<uint32_t> byte_code);

			void generate();
			void destroy() noexcept;
 
			inline VkShaderModule getShaderModule() const noexcept { return _shader; }
			inline VkShaderStageFlagBits getType() const noexcept { return _type; }

			inline const duets_array<fString, Uniform>& getUniforms() const { return _uniforms; }
			inline const duets_array<fString, VkVertexInputAttributeDescription>& getAttributes() const { return _attributes; }

			inline const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const { return _layouts; }

			inline std::optional<Uniform> getUniform(fString name) { return _uniforms.has(name) ? std::make_optional(_uniforms[name]) : std::nullopt; }
			inline std::optional<VkVertexInputAttributeDescription> getAttribute(fString name) { return _inputs.has(name) ? std::make_optional(_attributes[name]) : std::nullopt; }

			inline const fString& get_entry_point_name() const noexcept { return _entry_point_name; }

			~Shader() = default;

		private:
			duets_array<fString, Uniform> _uniforms;
			duets_array<fString, VkVertexInputAttributeDescription> _attributes;
			
			std::vector<VkDescriptorPoolSize> descriptorPools;
			std::vector<DescriptorSetLayout> _layouts;

			const std::vector<uint32_t> _byte_code;

			fString _entry_point_name;

			VkShaderModule _shader = VK_NULL_HANDLE;
			VkShaderStageFlagBits _type;
	};

	std::vector<uint32_t> load_spirv_from_file(fString path);
}

#endif // __AK_VK_SHADER__
