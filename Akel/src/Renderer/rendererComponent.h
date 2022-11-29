// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/09/2021
// Updated : 29/11/2022

#ifndef __AK_RENDERER_COMPONENT__
#define __AK_RENDERER_COMPONENT__

#include <Core/core.h>
#include <Graphics/entity.h>
#include <Platform/window.h>
#include <Utils/fStrings.h>
#include "Pipeline/vk_shader.h"
#include "Pipeline/vk_graphic_pipeline.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    enum class render_mode { mode_2D, mode_3D };

    class RendererComponent : public Component
    {
        public:
            RendererComponent(WindowComponent* window);

            inline void renderingMode(render_mode mode) noexcept { _mode = mode; }

			inline void loadCustomShader(std::vector<uint32_t> byte_code) { _shaders.push_back(std::move(byte_code)); }
			inline void loadCustomShader(fString path) { _shaders.push_back(load_spirv_from_file(std::move(path))); }

            void switchToShader(std::size_t index);

			inline constexpr void reloadRenderer() noexcept { _reload = true; }
			inline void setCullMode(VkCullModeFlags culling) noexcept { _cull_mode = culling; }

			inline void add_entity(Entity2D& entity) { _2D_entities.push_back(entity); }
			inline void add_entity(Entity3D& entity) { _3D_entities.push_back(entity); }

            void onAttach() override;
            void onRender() override;
            void update() override;
            void onQuit() override;

        private:
			GraphicPipeline _pipeline;
			std::vector<std::vector<uint32_t>> _shaders;

			std::vector<Entity3D> _3D_entities;
			std::vector<Entity2D> _2D_entities;

			VkCullModeFlags _cull_mode;
            
			render_mode _mode;
            
			WindowComponent* _window = nullptr;

			bool _reload = false;
    };
}

#endif // __AK_RENDERER_COMPONENT__
