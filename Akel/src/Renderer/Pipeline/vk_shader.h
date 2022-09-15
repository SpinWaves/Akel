// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 15/09/2022

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
					VertexInput(VkVertexInputBindingDescription binding, VkVertexInputAttributeDescription attribute) : _binding(std::move(binding)), _attribute(std::move(attribute)) {}

					const VkVertexInputBindingDescription& getBindingDescription() const { return _binding; }
					const VkVertexInputAttributeDescription& getAttributeDescription() const { return _attribute; }

					inline bool operator<(const VertexInput& rhs) const { return _binding.binding < rhs._binding.binding; }

				private:
					VkVertexInputBindingDescription _binding;
					VkVertexInputAttributeDescription _attribute;
			};

			enum class type { vertex, fragment, geometry, tesselation_evaluation, tesselation_control, compute };

			Shader(const std::vector<uint32_t> byte_code, type t);

			void generate();
			void destroy() noexcept;
 
			inline const VkShaderModule& getShaderModule() const noexcept { return _shader; }
			inline const type getType() const noexcept { return _type; }

			inline const duets_array<fString, Uniform>& getUniforms() const { return _uniforms; }
			inline const duets_array<fString, VkVertexInputAttributeDescription>& getAttributes() const { return _attributes; }

			inline const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const { return _desc_sets; }

			inline std::optional<Uniform> getUniform(fString name) { return _uniforms.has(name) ? std::make_optional(_uniforms[name]) : std::nullopt; }
			inline std::optional<VkVertexInputAttributeDescription> getAttribute(fString name) { return _attributes.has(name) ? std::make_optional(_attributes[name]) : std::nullopt; }

			inline const fString& get_entry_point_name() const noexcept { return _entry_point_name; }

			~Shader() = default;

		private:
			duets_array<fString, Uniform> _uniforms;
			duets_array<fString, VkVertexInputAttributeDescription> _attributes;

			std::vector<DescriptorSetLayout> _desc_sets;

			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkShaderModule _shader = VK_NULL_HANDLE;

			const std::vector<uint32_t> _byte_code;
			fString _entry_point_name;
			type _type;
	};

	Shader load_spirv_from_file(fString path, Shader::type t);
}

#endif // __AK_VK_SHADER__
