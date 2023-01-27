// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 21/12/2022

#ifndef __AK_VK_SHADER__
#define __AK_VK_SHADER__

#include <Akpch.h>
#include <Utils/Containers/duetsArray.h>
#include <Renderer/Descriptors/vk_descriptor_set.h>
#include <Renderer/Descriptors/vk_descriptor_set_layout.h>
#include <Renderer/Descriptors/vk_descriptor_pool.h>

namespace Ak
{
	class fString;

	class Shader
	{
		public:
			class Uniform
			{
				public:
					Uniform(int32_t binding = -1, int32_t set = -1, int32_t offset = -1, int32_t size = -1, VkShaderStageFlags stageFlags = 0, class UBO* ubo = nullptr) :
						_binding(binding),
						_set(set),
						_offset(offset),
						_size(size),
						_stageFlags(stageFlags),
						_buffer(ubo)
					{}

					inline int32_t getBinding() const noexcept { return _binding; }
					inline int32_t getOffset() const noexcept { return _offset; }
					inline int32_t getSize() const noexcept { return _size; }
					inline int32_t getSet() const noexcept { return _set; }
					inline class UBO* getBuffer() const noexcept { return _buffer; }
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

					~Uniform();

				private:
					class UBO* _buffer = nullptr;
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

			Shader(const std::vector<uint32_t> byte_code, class RendererComponent* renderer);

			void generate();
			void destroy() noexcept;
			void destroyModule() noexcept;

			inline VkShaderModule getShaderModule() const noexcept { return _shader; }
			inline VkShaderStageFlagBits getType() const noexcept { return _type; }

			inline std::unordered_map<std::string, Uniform>& getUniforms() { return _uniforms; }
			inline std::unordered_map<std::string, VkVertexInputAttributeDescription>& getAttributes() { return _attributes; }

			inline std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() { return _layouts; }
			inline DescriptorSetLayout& getDescriptorSetLayout(int index) { return _layouts[index]; }

			inline std::vector<DescriptorSet>& getDescriptorSets() { return _sets; }
			inline std::vector<VkDescriptorSet>& getVkDescriptorSets() { return _vk_sets; }

			inline std::optional<Uniform> getUniform(std::string name) { return _uniforms.count(std::move(name)) ? std::make_optional(_uniforms[name]) : std::nullopt; }
			inline std::optional<VkVertexInputAttributeDescription> getAttribute(std::string name) { return _attributes.count(std::move(name)) ? std::make_optional(_attributes[name]) : std::nullopt; }

			inline const fString& get_entry_point_name() const noexcept { return _entry_point_name; }

			~Shader() = default;

		private:
			std::unordered_map<std::string, Uniform> _uniforms;
			std::unordered_map<std::string, VkVertexInputAttributeDescription> _attributes;
			
			std::vector<VkDescriptorPoolSize> _desc_pool_sizes;
			DescriptorPool _desc_pool;
			std::vector<DescriptorSet> _sets;
			std::vector<VkDescriptorSet> _vk_sets;
			std::vector<DescriptorSetLayout> _layouts;

			const std::vector<uint32_t> _byte_code;

			fString _entry_point_name;
			class RendererComponent* _renderer = nullptr;

			VkShaderModule _shader = VK_NULL_HANDLE;
			VkShaderStageFlagBits _type;
	};

	std::vector<uint32_t> load_spirv_from_file(fString path);
}

#endif // __AK_VK_SHADER__
