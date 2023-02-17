// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 17/02/2023

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include "vk_pipeline.h"
#include <Renderer/Images/texture.h>
#include <Core/Memory/uniquePtrWrapper.h>
#include <Renderer/Pipeline/shaders_library.h>

namespace Ak
{
	struct AK_API PipelineDesc
	{
		std::vector<ShaderID> shaders;
		Texture* main_texture = nullptr;

		VkCullModeFlags culling = VK_CULL_MODE_BACK_BIT;
		VkPolygonMode mode = VK_POLYGON_MODE_FILL;
		VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		float line_width = 1.0f;

		inline constexpr bool operator==(const PipelineDesc& other) noexcept
		{
			bool same_shaders = true;
			for(int i = 0; i < shaders.size(); i++)
			{
				if(shaders.size() != other.shaders.size())
				{
					same_shaders = false;
					break;
				}
				if(ShadersLibrary::get().getShader(shaders[i])->_byte_code != ShadersLibrary::get().getShader(other.shaders[i])->_byte_code)
					same_shaders = false;
			}
			return	(culling == other.culling) && (mode == other.mode) && (topology == other.topology) &&
					(line_width == other.line_width) && (main_texture == other.main_texture) && same_shaders;
		}
	};

	class AK_API GraphicPipeline : public Pipeline
	{
		public:
			GraphicPipeline() = default;

			void init(class RendererComponent* renderer, PipelineDesc& desc);
			void bindPipeline(CmdBuffer& commandBuffer) noexcept override;
			void destroy() noexcept;

			inline const VkPipeline& getPipeline() const override { return _graphicsPipeline; }
			inline const VkPipelineLayout& getPipelineLayout() const override { return _pipelineLayout; }
			inline const VkPipelineBindPoint& getPipelineBindPoint() const override { return _pipelineBindPoint; }
			inline PipelineDesc& getDescription() noexcept { return _desc; }
			
			~GraphicPipeline() = default;

		private:
			PipelineDesc _desc;
			VkPipeline _graphicsPipeline = VK_NULL_HANDLE;
			VkPipelineCache _cache = VK_NULL_HANDLE;
			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkPipelineBindPoint _pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			class RendererComponent* _renderer = nullptr;
			Unique_ptr<Texture> _dummy = nullptr;
	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
