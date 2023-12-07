// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 06/11/2023

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
					Uniform(int32_t binding = -1, int32_t set = -1, int32_t offset = -1, int32_t size = -1, VkShaderStageFlagBits stageFlags = VK_SHADER_STAGE_VERTEX_BIT, class UBO* ubo = nullptr) :
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
					inline VkShaderStageFlagBits getStageFlags() const noexcept { return _stageFlags; }

					inline bool operator==(const Uniform& rhs) const
					{
						return  _binding == rhs._binding &&
								_offset == rhs._offset &&
								_size == rhs._size &&
								_set == rhs._set && 
								_stageFlags == rhs._stageFlags;
					}

					inline bool operator!=(const Uniform& rhs) const { return !operator==(rhs); }
					void destroy() noexcept;

					~Uniform() = default;

				private:
					class UBO* _buffer = nullptr;
					VkShaderStageFlagBits _stageFlags;
					int32_t _binding;
					int32_t _set;
					int32_t _offset;
					int32_t _size;
			};

			class ImageSampler
			{
				public:
					ImageSampler(int32_t binding = -1, int32_t set = -1, int32_t offset = -1, int32_t size = -1, VkShaderStageFlagBits stageFlags = VK_SHADER_STAGE_VERTEX_BIT) :
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
					inline VkShaderStageFlagBits getStageFlags() const noexcept { return _stageFlags; }

					inline bool operator==(const ImageSampler& rhs) const
					{
						return  _binding == rhs._binding &&
								_offset == rhs._offset &&
								_size == rhs._size &&
								_set == rhs._set && 
								_stageFlags == rhs._stageFlags;
					}

					inline bool operator!=(const ImageSampler& rhs) const { return !operator==(rhs); }

					~ImageSampler() = default;

				private:
					VkShaderStageFlagBits _stageFlags;
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

			class PushConstant
			{
				public:
					PushConstant(int32_t offset = -1, int32_t size = -1, VkShaderStageFlagBits stage = VK_SHADER_STAGE_VERTEX_BIT) :
						_offset(offset),
						_size(size),
						_stage(stage)
					{}

					inline int32_t getOffset() const noexcept { return _offset; }
					inline int32_t getSize() const noexcept { return _size; }
					inline VkShaderStageFlagBits getStageFlags() const noexcept { return _stage; }

					inline void setData(const void* data) noexcept { _data = const_cast<void*>(data); }
					inline void bind(VkCommandBuffer buffer, VkPipelineLayout layout) noexcept { vkCmdPushConstants(buffer, layout, _stage, _offset, _size, _data); }

					~PushConstant() = default;

				private:
					void* _data = nullptr;
					VkShaderStageFlagBits _stage;
					int32_t _offset;
					int32_t _size;
			};

			Shader(const std::vector<uint32_t> byte_code, class RendererComponent* renderer);

			void destroy() noexcept;
			void destroyModule() noexcept;

			inline VkShaderModule getShaderModule() const noexcept { return _shader; }
			inline VkShaderStageFlagBits getType() const noexcept { return _type; }

			inline std::unordered_map<std::string, Uniform>& getUniforms() { return _uniforms; }
			inline std::unordered_map<std::string, ImageSampler>& getImageSamplers() { return _image_samplers; }
			inline std::unordered_map<std::string, PushConstant>& getPushConstants() { return _push_constants; }
			inline std::unordered_map<std::string, VkVertexInputAttributeDescription>& getAttributes() { return _attributes; }

			inline std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() { return _layouts; }
			inline DescriptorSetLayout& getDescriptorSetLayout(int index) { return _layouts[index]; }

			inline const std::vector<DescriptorSet>& getDescriptorSets() const { return _sets; }
			inline const std::vector<VkDescriptorSet>& getVkDescriptorSets() const { return _vk_sets; }
			std::optional<DescriptorSet> getDescriptorSetContaining(const std::string& name);

			inline std::optional<Uniform> getUniform(const std::string& name) { return _uniforms.count(name) ? std::make_optional(_uniforms[name]) : std::nullopt; }
			inline std::optional<ImageSampler> getImageSampler(const std::string& name) { return _image_samplers.count(name) ? std::make_optional(_image_samplers[name]) : std::nullopt; }
			inline std::optional<PushConstant> getPushConstant(const std::string& name) { return _push_constants.count(name) ? std::make_optional(_push_constants[name]) : std::nullopt; }
			inline std::optional<VkVertexInputAttributeDescription> getAttribute(const std::string& name) { return _attributes.count(name) ? std::make_optional(_attributes[name]) : std::nullopt; }

			inline const fString& getEntryPointName() const noexcept { return _entry_point_name; }
			inline const std::vector<uint32_t>& getByteCode() const { return _byte_code; }

			~Shader() = default;

		private:
			friend class PipelineDesc;
			friend class GraphicPipeline;
			void generate();

		private:
			std::unordered_map<std::string, Uniform> _uniforms;
			std::unordered_map<std::string, ImageSampler> _image_samplers;
			std::unordered_map<std::string, PushConstant> _push_constants;
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

			bool _is_init = false;
	};

	std::vector<uint32_t> load_spirv_from_file(std::filesystem::path path);
}

#endif // __AK_VK_SHADER__
