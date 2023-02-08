// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2023
// Updated : 08/02/2023

#include <Graphics/skybox.h>
#include <Renderer/rendererComponent.h>
#include <Scene/scene.h>
#include <Scene/shaderLoader.h>
#include <Graphics/builtin_shaders.h>

namespace Ak
{
	Skybox::Skybox(std::shared_ptr<ImageCube> image, RendererComponent* renderer) : _image(std::move(image)), _renderer(renderer) {}

	void Skybox::init(Scene& scene) noexcept
	{
		std::vector<std::vector<uint32_t>> shaders;

		shaders.push_back(std::move(scene._loader->loadShader(shaderlang::nzsl, std::string_view{skybox_vertex_shader})));
		shaders.push_back(std::move(scene._loader->loadShader(shaderlang::nzsl, std::string_view{skybox_fragment_shader})));
		_pipeline.init(*_renderer, std::move(shaders));
	}
}
