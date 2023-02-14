// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 14/02/2023

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include "vk_pipeline.h"
#include <Renderer/Images/texture.h>
#include <Core/Memory/uniquePtrWrapper.h>

namespace Ak
{
	struct AK_API PipelineDesc
	{
		Texture* main_texture = nullptr;

		VkCullModeFlags culling = VK_CULL_MODE_BACK_BIT;
		VkPolygonMode mode = VK_POLYGON_MODE_FILL;
		VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		float line_width = 1.0f;
	};

	class AK_API GraphicPipeline : public Pipeline
	{
		public:
			void init(class RendererComponent& renderer, std::vector<std::vector<uint32_t>> shaders, const PipelineDesc& desc);
			void destroy() noexcept;

			inline std::vector<Shader>& getShaders() override { return _shaders; }
			inline const VkPipeline& getPipeline() const override { return _graphicsPipeline; }
			inline const VkPipelineLayout& getPipelineLayout() const override { return _pipelineLayout; }
			inline const VkPipelineBindPoint& getPipelineBindPoint() const override { return _pipelineBindPoint; }

		private:
			PipelineDesc _desc;
			std::vector<Shader> _shaders;
			VkPipeline _graphicsPipeline = VK_NULL_HANDLE;
			VkPipelineCache _cache = VK_NULL_HANDLE;
			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkPipelineBindPoint _pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			Unique_ptr<Texture> _dummy = nullptr;
	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
