// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 12/04/2022

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
					int32_t _binding;
					int32_t _offset;
					int32_t _size;
					int32_t _type;
					bool _readOnly;
					bool _writeOnly;
					VkShaderStageFlags _stageFlags;
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
					int32_t _binding;
					int32_t _size;
					VkShaderStageFlags _stageFlags;
					std::unordered_map<std::string, Uniform> _uniforms;
			};

			class Vertex_input
			{
				public:
					Vertex_input(std::vector<VkVertexInputBindingDescription> bindings = {}, std::vector<VkVertexInputAttributeDescription> attributes = {}) : _bindings(std::move(bindings)), _attributes(std::move(attributes)) {}

					const std::vector<VkVertexInputBindingDescription>& getBindingDescriptions() const { return _binding; }
					const std::vector<VkVertexInputAttributeDescription>& getAttributeDescriptions() const { return _attributes; }

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

			enum class type { vertex, fragment, geometry, tesselation };

			Shader(const fString path, type t);

			void generate();
			inline void destroy()
			{
				static_assert(_shader != VK_NULL_HANDLE, "trying to destroy an uninit shader");
				vkDestroyShaderModule(Render_Core::get().getDevice().get(), _shader, nullptr);
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
