// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/10/2023
// Updated : 02/11/2023

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
		std::vector<VkDescriptorSet> descriptor_sets;
		std::vector<ShaderID> shaders;
		DepthImage depth;
		const Cam::BaseCamera& camera;
		TextureID render_texture = nulltexture;
	};

	struct ForwardData : public CommonForwardData
	{
		CommandDataQueue command_queue;
		std::vector<Shader::PushConstant> push_constants;
	};

	struct ForwardSkyboxData : public CommonForwardData
	{
	};

	struct ForwardPassDescription
	{
		ForwardData fdata;
		ForwardSkyboxData skydata;
		bool geometryPass = true;
		bool skyboxPass = true;
	};

	class AK_API ForwardPass
	{
		public:
			ForwardPass() = default;
			void process(const RendererComponent& renderer, const ForwardPassDescription& desc);
			~ForwardPass() = default;

		private:
			void forwardPass(const RendererComponent& renderer, const ForwardData& data);
			void skyboxPass(const RendererComponent& renderer, const ForwardSkyboxData& data);

		private:
			PipelinesManager _pipelines_manager;
	};
}

#endif
