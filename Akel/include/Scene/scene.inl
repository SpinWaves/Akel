// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 14/10/2023

namespace Ak
{
	template <shaderlang lang, shaderType type>
	void Scene::loadCustomShader(std::filesystem::path path)
	{
		if(lang == shaderlang::spirv)
		{
			std::shared_ptr<Shader> shader = create_shared_ptr_w<Shader>(load_spirv_from_file(path.c_str()), _renderer);
			_forward_shaders[static_cast<uint8_t>(type)] = ShadersLibrary::get().addShaderToLibrary(std::move(shader));
		}
		else
			_loadCustomShader(type, lang, std::move(path));
	}

	template <typename T, typename ... Args>
	void Scene::addCamera(Args&& ... args)
	{
		static_assert(std::is_base_of<Cam::BaseCamera, T>::value, "Scene camera must inherit from Ak::Cam::BaseCamera");
		T* cam = memAlloc<T>(std::forward<Args>(args)...);
		if(_camera)
			_camera.reset(cam);
		else
			_camera = makeUniquePtr<Cam::BaseCamera>(cam);
	}
}
