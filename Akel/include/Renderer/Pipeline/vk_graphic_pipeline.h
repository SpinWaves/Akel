// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 23/08/2023

#ifndef __AK_VK_GRAPHIC_PIPELINE__
#define __AK_VK_GRAPHIC_PIPELINE__

#include "vk_pipeline.h"
#include <Renderer/Images/texture.h>
#include <Core/Memory/uniquePtrWrapper.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Renderer/RenderPass/vk_render_pass.h>
#include <Renderer/Images/texture_library.h>
#include <Renderer/Images/depth.h>

namespace Ak
{
	struct AK_API PipelineDesc
	{
		std::vector<ShaderID> shaders;
		std::array<TextureID, MAX_RENDER_TARGETS> render_targets = { nulltexture };
		std::array<float, 4> clear_color;
		DepthImage* depth = nullptr;
		VkCullModeFlags culling = VK_CULL_MODE_BACK_BIT;
		VkPolygonMode mode = VK_POLYGON_MODE_FILL;
		VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		float line_width = 1.0f;
		bool swapchain = false;
		bool clear_target = false;
	};

	class AK_API GraphicPipeline : public Pipeline
	{
		public:
			GraphicPipeline() = default;

			void init(class RendererComponent* renderer, PipelineDesc& desc);
			bool bindPipeline(CmdBuffer& commandBuffer) noexcept override;
			void endPipeline(CmdBuffer& commandBuffer) noexcept override;
			void destroy() noexcept;

			inline const VkPipeline& getPipeline() const override { return _graphicsPipeline; }
			inline const VkPipelineLayout& getPipelineLayout() const override { return _pipelineLayout; }
			inline const VkPipelineBindPoint& getPipelineBindPoint() const override { return _pipelineBindPoint; }
			inline PipelineDesc& getDescription() noexcept { return _desc; }
			
			~GraphicPipeline() = default;

		private:
			void createFrameBuffers();
			void transitionAttachements();

		private:
			std::vector<std::shared_ptr<FrameBuffer>> _frame_buffers;
			PipelineDesc _desc;
			std::shared_ptr<RenderPass> _render_pass;
			VkPipeline _graphicsPipeline = VK_NULL_HANDLE;
			VkPipelineCache _cache = VK_NULL_HANDLE;
			VkPipelineLayout _pipelineLayout = VK_NULL_HANDLE;
			VkPipelineBindPoint _pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			class RendererComponent* _renderer = nullptr;
	};
}

#endif // __AK_VK_GRAPHIC_PIPELINE__
