// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/10/2023
// Updated : 06/11/2023

#ifndef __AK_FORWARD_PASS__
#define __AK_FORWARD_PASS__

#include <Akpch.h>
#include <Graphics/render_command.h>
#include <Renderer/Images/depth.h>
#include <Renderer/Images/texture.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Renderer/rendererComponent.h>
#include <Scene/Cameras/base_camera.h>
#include <Renderer/Pipeline/pipelines_manager.h>

namespace Ak
{
	struct CommonForwardData
	{
		std::vector<ShaderID> shaders;
		DepthImage depth;
		std::shared_ptr<Cam::BaseCamera> camera;
		TextureID render_texture = nulltexture;
	};

	struct ForwardData : public CommonForwardData
	{
		CommandDataQueue command_queue;
	};

	struct ForwardSkyboxData : public CommonForwardData
	{
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
