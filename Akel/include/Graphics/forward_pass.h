// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/10/2023
// Updated : 17/10/2023

#ifndef __AK_FORWARD_PASS__
#define __AK_FORWARD_PASS__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Renderer/Images/depth.h>
#include <Renderer/Images/texture.h>
#include <Renderer/Pipeline/shaders_library.h>

namespace Ak
{
	struct ForwardData
	{
		CommandDataQueue command_queue;
		std::vector<VkDescriptorSet> descriptor_sets;
		std::vector<Shader::PushConstant> push_constants;
		std::vector<ShaderID> shaders;
		DepthImage depth;
		TextureID render_texture = nulltexture;
	};

	class AK_API ForwardPass
	{
		public:
			ForwardPass() = default;
			void process(const ForwardData& data);
			~ForwardPass() = default;

		private:
	};
}

#endif
