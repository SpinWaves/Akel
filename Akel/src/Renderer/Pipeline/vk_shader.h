// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 30/05/2022

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

					inline bool operator==(const Uniform &rhs) const { return _binding == rhs._binding && _offset == rhs._offset && _size == rhs._size && _set == rhs._set && _stageFlags == rhs._stageFlags; }
					inline bool operator!=(const Uniform &rhs) const { return !operator==(rhs); }

				private:
					VkShaderStageFlags _stageFlags;
					int32_t _binding;
					int32_t _set;
					int32_t _offset;
					int32_t _size;
			};

			class Vertex_input
			{
				public:
					Vertex_input(std::vector<VkVertexInputBindingDescription> bindings = {}, std::vector<VkVertexInputAttributeDescription> attributes = {}) : _bindings(std::move(bindings)), _attributes(std::move(attributes)) {}

					const std::vector<VkVertexInputBindingDescription>& getBindingDescriptions() const { return _bindings; }
					const std::vector<VkVertexInputAttributeDescription>& getAttributeDescriptions() const { return _attributes; }

					inline bool operator<(const Vertex_input& rhs) const { return _bindings.front().binding < rhs._bindings.front().binding; }

				private:
					std::vector<VkVertexInputBindingDescription> _bindings;
					std::vector<VkVertexInputAttributeDescription> _attributes;
			};

			class Attribute
			{
				public:
					Attribute(int32_t binding, int32_t location, int32_t offset, int32_t format) : _binding(binding), _location(location), _offset(offset), _format(format) {}

					inline int32_t getBinding() const noexcept { return _binding; }
					inline int32_t getLocation() const noexcept { return _location; }
					inline int32_t getOffest() const noexcept { return _offset; }
					inline int32_t getFormat() const noexcept { return _format; }

					inline bool operator==(const Attribute &rhs) const noexcept { return _binding == rhs._binding && _location == rhs._location && _offset == rhs._offset && _format == rhs._format; }
					inline bool operator!=(const Attribute &rhs) const noexcept { return !operator==(rhs); }

					inline VkVertexInputAttributeDescription convert_to_vk_vertex_input_attribute() const noexcept { return VkVertexInputAttributeDescription{_binding, _location, static_cast<VkFormat>(_format), _offset}; }

					Attribute() = default;

				private:
					int32_t _binding = 0;
					int32_t _location = 0;
					int32_t _offset = 0;
					int32_t _format = 0;
			};
 
			enum class type { vertex, fragment, geometry, tesselation_evaluation, tesselation_control, compute };

			Shader(const std::vector<uint32_t> byte_code, type t);

			void generate();
			void destroy() noexcept;
 
			inline const VkShaderModule& getShaderModule() noexcept { return _shader; }
			inline const type getType() noexcept { return _type; }

			inline const duets_array<fString, Uniform>& getUniforms() { return _uniforms; }
			inline const duets_array<fString, Attribute>& getAttributes() { return _attributes; }

			inline const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() { return _desc_sets; }

			inline std::optional<Uniform> getUniform(fString name) { return _uniforms.has(name) ? std::make_optional(_uniforms[name]) : std::nullopt; }
			inline std::optional<Attribute> getAttribute(fString name) { return _attributes.has(name) ? std::make_optional(_attributes[name]) : std::nullopt; }

			~Shader() = default;

		private:
			duets_array<fString, Uniform> _uniforms;
			duets_array<fString, Attribute> _attributes;

			std::vector<DescriptorSetLayout> _desc_sets;

			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkShaderModule _shader = VK_NULL_HANDLE;

			const std::vector<uint32_t> _byte_code;
			type _type;
	};

	Shader load_spirv_from_file(fString path, Shader::type t);
}

#endif // __AK_VK_SHADER__
