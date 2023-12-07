// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/10/2023
// Updated : 02/12/2023

#ifndef __AK_FORWARD_PASS__
#define __AK_FORWARD_PASS__

#include <Akpch.h>
#include <Graphics/render_command.h>
#include <Renderer/Images/depth.h>
#include <Renderer/Images/texture.h>
#include <Renderer/Images/cubemap_library.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Renderer/rendererComponent.h>
#include <Scene/Cameras/base_camera.h>
#include <Renderer/Pipeline/pipelines_manager.h>

namespace Ak
{
	struct CommonForwardData
	{
		DepthImage depth;
		std::shared_ptr<Cam::BaseCamera> camera;
		TextureID render_texture = nulltexture;
	};

	struct ForwardData : public CommonForwardData
	{
		std::vector<ShaderID> shaders;
		CommandDataQueue command_queue;

		inline void setCommonData(const CommonForwardData& data)
		{
			depth = data.depth;
			camera = data.camera;
			render_texture = data.render_texture;
		}
	};

	struct ForwardSkyboxData : public CommonForwardData
	{
		std::vector<ShaderID> shaders;
		CubemapID cubemap = nullcubemap;

		inline void setCommonData(const CommonForwardData& data)
		{
			depth = data.depth;
			camera = data.camera;
			render_texture = data.render_texture;
		}
	};

	struct ForwardPassDescription
	{
		ForwardData* fdata = nullptr;
		ForwardSkyboxData* skydata = nullptr;
	};

	class AK_API ForwardPass
	{
		public:
			ForwardPass();
			void init();
			void process(RendererComponent& renderer, const ForwardPassDescription& desc, bool rebuildPass);
			void destroy();
			~ForwardPass() = default;

		private:
			void forwardPass(RendererComponent& renderer, const ForwardData& data, bool rebuildPass);
			void skyboxPass(RendererComponent& renderer, const ForwardSkyboxData& data, bool rebuildPass);

		private:
			PipelinesManager _pipelines_manager;
	};
}

#endif
