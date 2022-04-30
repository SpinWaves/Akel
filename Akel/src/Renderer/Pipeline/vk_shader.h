// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 30/04/2022

#ifndef __AK_VK_SHADER__
#define __AK_VK_SHADER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>
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
					Uniform(int32_t binding = -1, int32_t offset = -1, int32_t size = -1, int32_t type = -1, bool readOnly = false, bool writeOnly = false, VkShaderStageFlags stageFlags = 0) :
						_binding(binding),
						_offset(offset),
						_size(size),
						_type(type),
						_readOnly(readOnly),
						_writeOnly(writeOnly),
						_stageFlags(stageFlags)
					{}

					inline int32_t getBinding() const noexcept { return _binding; }
					inline int32_t getOffset() const noexcept { return _offset; }
					inline int32_t getSize() const noexcept { return _size; }
					inline int32_t getType() const noexcept { return _type; }
					inline bool isReadOnly() const noexcept { return _readOnly; }
					inline bool isWriteOnly() const noexcept { return _writeOnly; }
					inline VkShaderStageFlags getStageFlags() const noexcept { return _stageFlags; }

					inline bool operator==(const Uniform &rhs) const { return binding == rhs.binding && offset == rhs.offset && size == rhs.size && glType == rhs.glType && readOnly == rhs.readOnly && writeOnly == rhs.writeOnly && stageFlags == rhs.stageFlags; }
					inline bool operator!=(const Uniform &rhs) const { return !operator==(rhs); }

				private:
					VkShaderStageFlags _stageFlags;
					int32_t _binding;
					int32_t _offset;
					int32_t _size;
					int32_t _type;
					bool _readOnly;
					bool _writeOnly;
			};

			class Uniform_block
			{
				public:
					UniformBlock(int32_t binding = -1, int32_t size = -1, VkShaderStageFlags stageFlags = 0) : _binding(binding), _size(size), _stageFlags(stageFlags) {}

					inline int32_t getBinding() const noexcept { return binding; }
					inline int32_t getSize() const noexcept { return size; }
					inline VkShaderStageFlags getStageFlags() const noexcept { return stageFlags; }
					inline const std::unordered_map<std::string, Uniform>& getUniforms() const noexcept { return uniforms; }

					inline std::optional<Uniform> getUniform(const std::string &name) const { return (auto it = uniforms.find(name)) == uniforms.end() ? std::nullopt : it->second; }

					inline bool operator==(const UniformBlock &rhs) const { return binding == rhs.binding && size == rhs.size && stageFlags == rhs.stageFlags && type == rhs.type && uniforms == rhs.uniforms; }
					inline bool operator!=(const UniformBlock &rhs) const { return !operator==(rhs); }

				private:
					std::unordered_map<std::string, Uniform> _uniforms;
					VkShaderStageFlags _stageFlags;
					int32_t _binding;
					int32_t _size;
			};

			class Vertex_input
			{
				public:
					Vertex_input(std::vector<VkVertexInputBindingDescription> bindings = {}, std::vector<VkVertexInputAttributeDescription> attributes = {}) : _bindings(std::move(bindings)), _attributes(std::move(attributes)) {}

					const std::vector<VkVertexInputBindingDescription>& getBindingDescriptions() const { return _binding; }
					const std::vector<VkVertexInputAttributeDescription>& getAttributeDescriptions() const { return _attributes; }

					inline bool operator<(const Vertex_input &rhs) const { return bindingDescriptions.front()._bindings < rhs.bindingDescriptions.front()._bindings; }

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

					inline VkVertexInputAttributeDescription convert_to_vk_vertex_input_attribute() const noexcept { return VkVertexInputAttributeDescription{_binding, _location, _format, _offset}; }

					Attribute() = default;

				private:
					int32_t _binding = 0;
					int32_t _location = 0;
					int32_t _offset = 0;
					int32_t _format = 0;
			};
 
			enum class type { vertex, fragment, geometry, tesselation_evaluation, tesselation_control, compute };
			enum class lang { glsl, spirv }; // more languages will be added

			Shader(const std::filesystem::path path, lang l, type t);
			Shader(const std::filesystem::path path, lang l);

			void generate();
			inline void destroy() noexcept
			{
				static_assert(_shader != VK_NULL_HANDLE, "trying to destroy an uninit shader");
				vkDestroyShaderModule(Render_Core::get().getDevice().get(), _shader, nullptr);

				for(auto& desc : _desc_sets)
					desc.destroy();

				static_assert(_pipelineLayout != VK_NULL_HANDLE, "trying to destroy an uninit pipeline layout");
				vkDestroyPipelineLayout(Render_Core::get().getDevice().get(), _pipelineLayout, nullptr);
			}
 
			inline const fString& getName() const { return _name; }
			inline const VkShaderModule& getShaderModule() const noexcept { return _shader; }
			inline const type getType() const noexcept { return _type; }

			inline const std::unordered_map<fString, Uniform>& getUniforms() const { return _uniforms; };
			inline const std::unordered_map<fString, Uniform_block>& getUniformBlocks() const { return _uniformBlocks; };
			inline const std::unordered_map<fString, Attribute>& getAttributes() const { return _attributes; };

			inline const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const { return _desc_sets; }

			inline std::optional<Uniform> getUniform(const fString name) const { return auto it = _uniforms.find(name); it != _uniforms.end() ? it->second : std::nullopt; }
			inline std::optional<Uniform_block> getUniformBlock(const fString name) const { return auto it = _uniformBlocks.find(name); it != _uniformBlocks.end() ? it->second : std::nullopt; }
			inline std::optional<Attribute> getAttribute(const fString name) const { return auto it = _attributes.find(name); it != _attributes.end() ? it->second : std::nullopt; }

			~Shader() = default;

		private:
			std::unordered_map<fString, Uniform_block> _uniformBlocks;
			std::unordered_map<fString, Uniform> _uniforms;
			std::unordered_map<fString, Attribute> _attributes;

			std::vector<DescriptorSetLayout> _desc_sets;

			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkShaderModule _shader = VK_NULL_HANDLE;

			const std::filesystem::path _file;
			type _type;
			lang _lang;
	};
}

#endif // __AK_VK_SHADER__
