// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 24/07/2023

#ifndef __AK_IMGUI_RENDER_STATISTICS__
#define __AK_IMGUI_RENDER_STATISTICS__

#include <Akpch.h>
#include <Modules/ImGui/imgui_component.h>

namespace Ak
{
	class AK_API ImGuiRenderStats : public ImGuiComponent
	{
		public:
			ImGuiRenderStats(class RendererComponent* renderer);
			void onRender() override;
			virtual ~ImGuiRenderStats() = default;
	};
}

#endif
