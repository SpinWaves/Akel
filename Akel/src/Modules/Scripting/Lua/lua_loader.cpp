// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/11/2022
// Updated : 28/03/2023

#include <Modules/Scripting/Lua/lua_loader.h>
#include <Modules/Scripting/Lua/lua_script.h>
#include <Platform/input.h>
#include <Core/core.h>
#include <Maths/maths.h>
#include <Scene/Attributes/attributes.h>
#include <Scene/scene_manager.h>

namespace Ak
{
	static std::optional<sol::state> state;
	Entity* __entity;

	LuaLoader::LuaLoader(Application* app, SceneManager& scene_manager) : ScriptLoader()
	{
		if(state)
			return;
		state = sol::state();
		state->open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::table, sol::lib::os, sol::lib::string);
		bindLogs();
		bindInputs(app->getInput());
		bindMaths();
		bindAudioEngine();
		bindECS();
		bindSceneManager(scene_manager);
	}

	Script* LuaLoader::loadScript(std::filesystem::path lua_file)
	{
		if(!std::filesystem::exists(lua_file))
		{
			Core::log::report(ERROR, "Lua Loader : invalid script path '%s'", lua_file.string().c_str());
			return nullptr;
		}
		
		LuaScript* script;
		sol::environment env(*state, sol::create, state->globals());

		auto sol_script = state->script_file(lua_file.string(), env, sol::script_pass_on_error);
		if(!sol_script.valid())
		{
			sol::error err = sol_script;
			Core::log::report(ERROR, "Lua Error : %s", err.what());
			Core::log::report(ERROR, "Lua Loader : failed to load and execute Lua script '%s'", lua_file.string().c_str());
			return nullptr;
		}

		script = memAlloc<LuaScript>();
		script->_env = std::move(env);

		script->_on_init = script->_env["AkelOnInit"];
		script->_on_update = script->_env["AkelOnUpdate"];
		script->_on_quit = script->_env["AkelOnQuit"];

		state->collect_garbage();

		return script;
	}

	void LuaLoader::bindLogs()
	{
		auto log = (*state)["Ak"].get_or_create<sol::table>()["log"].get_or_create<sol::table>();

		log.set_function("Message", [](std::string message)
				{ Core::log::report(MESSAGE, "Lua : %s", message.c_str()); });
		log.set_function("Warning", [](std::string message)
				{ Core::log::report(WARNING, "Lua : %s", message.c_str()); });
		log.set_function("StrongWarning", [](std::string message)
				{ Core::log::report(STRONG_WARNING, "Lua : %s", message.c_str()); });
		log.set_function("Error", [](std::string message)
				{ Core::log::report(ERROR, "Lua : %s", message.c_str()); });
		log.set_function("FatalError", [](std::string message)
				{ Core::log::report(FATAL_ERROR, "Lua : %s", message.c_str()); });
	}

	void LuaLoader::bindInputs(const Input& in)
	{
		auto input = (*state)["Ak"].get_or_create<sol::table>();

		input.set_function("getInKey", [&](SDL_Scancode key, action kind) -> bool
				{ return in.getInKey(key, kind); });
		input.set_function("getInMouse", [&](uint8_t key, action kind) -> bool
				{ return in.getInMouse(key, kind); });
		input.set_function("isMouseMoving", [&]() -> bool
				{ return in.isMouseMoving(); });

		input.set_function("getMouseX", [&]() -> int
				{ return in.getX(); });
		input.set_function("getMouseY", [&]() -> int
				{ return in.getY(); });
		input.set_function("getMouseXRel", [&]() -> int
				{ return in.getXRel(); });
		input.set_function("getMouseYRel", [&]() -> int
				{ return in.getYRel(); });

		input.set_function("finish", [&]() -> void
				{ return const_cast<Input&>(in).finish(); });
		input.set_function("run", [&]() -> void
				{ return const_cast<Input&>(in).run(); });

		std::initializer_list<std::pair<sol::string_view, action>> actions = {
			{ "down", action::down },
			{ "up", action::up },
        };
        input.new_enum<action, false>("action", actions);

		std::initializer_list<std::pair<sol::string_view, SDL_Scancode>> keyItems = {
			{ "A", AK_KEY_A },
			{ "B", AK_KEY_B },
			{ "C", AK_KEY_C },
			{ "D", AK_KEY_D },
			{ "E", AK_KEY_E },
			{ "F", AK_KEY_F },
			{ "G", AK_KEY_G },
			{ "H", AK_KEY_H },
			{ "I", AK_KEY_I },
			{ "J", AK_KEY_J },
			{ "K", AK_KEY_K },
			{ "L", AK_KEY_L },
			{ "M", AK_KEY_M },
			{ "N", AK_KEY_N },
			{ "O", AK_KEY_O },
			{ "P", AK_KEY_P },
			{ "Q", AK_KEY_Q },
			{ "R", AK_KEY_R },
			{ "S", AK_KEY_S },
			{ "T", AK_KEY_T },
			{ "U", AK_KEY_U },
			{ "V", AK_KEY_V },
			{ "W", AK_KEY_W },
			{ "X", AK_KEY_X },
			{ "Y", AK_KEY_Y },
			{ "Z", AK_KEY_Z },

			{ "k0", AK_KEY_0 },
			{ "k1", AK_KEY_1 },
			{ "k2", AK_KEY_2 },
			{ "k3", AK_KEY_3 },
			{ "k4", AK_KEY_4 },
			{ "k5", AK_KEY_5 },
			{ "k6", AK_KEY_6 },
			{ "k7", AK_KEY_7 },
			{ "k8", AK_KEY_8 },
			{ "k9", AK_KEY_9 },

			{ "up", AK_KEY_UP },
			{ "down", AK_KEY_DOWN },
			{ "left", AK_KEY_LEFT },
			{ "right", AK_KEY_RIGHT },
        };
        input.new_enum<SDL_Scancode, false>("key", keyItems);

		std::initializer_list<std::pair<sol::string_view, uint8_t>> mouseItems = {
			{ "left", AK_MOUSE_BUTTON_LEFT },
			{ "middle", AK_MOUSE_BUTTON_MIDDLE },
			{ "right", AK_MOUSE_BUTTON_RIGHT },
			{ "x1", AK_MOUSE_BUTTON_X1 },
			{ "x2", AK_MOUSE_BUTTON_X2 },
        };
        input.new_enum<uint8_t, false>("mouse", mouseItems);
	}

	void LuaLoader::bindMaths()
	{
		auto lua = (*state)["Ak"].get_or_create<sol::table>();

		using namespace Maths;

		lua.new_usertype<Vec2f>(
			"Vec2",
			sol::constructors<sol::types<>, sol::types<float, float>>(),
			"X", &Vec2f::X,
			"Y", &Vec2f::Y,
			"length", &Vec2f::length,
			"normalize", &Vec2f::normalize,
			sol::meta_function::addition, [](const Vec2f& a, const Vec2f& b)
			{ return a + b; },
			sol::meta_function::subtraction, [](const Vec2f& a, const Vec2f& b)
			{ return a - b; },
			sol::meta_function::multiplication, [](Vec2f& a, Vec2f& b)
            { return a * b; },
//			sol::meta_function::unary_minus, [](Vec2f& v) -> Vec2f
//			{ return -v; },
			sol::meta_function::equal_to, [](Vec2f& a, Vec2f& b)
			{ return a == b; }
		);

		auto vec3_mult_overloads = sol::overload(
			//[](const Vec3f& v1, const Vec3f& v2) -> Vec3f
			//{ return v1 * v2; },
			[](const Vec3f& v1, float f) -> Vec3f
			{ return v1 * f; },
			[](float f, const Vec3f& v1) -> Vec3f
			{ return f * v1; }
		);

		lua.new_usertype<Vec3f>(
			"Vec3",
			sol::constructors<sol::types<>, sol::types<float, float, float>>(),
			"X", &Vec3f::X,
			"Y", &Vec3f::Y,
			"Z", &Vec3f::Z,
			"length", &Vec3f::length,
			"normalize", &Vec3f::normalize,
			"absolute", &Vec3f::absolute,
			sol::meta_function::addition, [](const Vec3f& a, const Vec3f& b)
			{ return a + b; },
			sol::meta_function::multiplication, vec3_mult_overloads,
			sol::meta_function::subtraction, [](const Vec3f& a, const Vec3f& b)
			{ return a - b; },
			sol::meta_function::unary_minus, [](Vec3f& v) -> Vec3f
			{ return -v; },
			sol::meta_function::equal_to, [](Vec3f& a, Vec3f& b)
			{ return a == b; }
		);

		auto vec4_mult_overloads = sol::overload(
			//[](const Vec3f& v1, const Vec3f& v2) -> Vec3f
			//{ return v1 * v2; },
			[](const Vec4f& v1, float f) -> Vec4f
			{ return v1 * f; },
			[](float f, const Vec4f& v1) -> Vec4f
			{ return f * v1; }
		);

		lua.new_usertype<Vec4f>(
			"Vec4",
			sol::constructors<sol::types<>, sol::types<float, float, float, float>>(),
			"X", &Vec4f::X,
			"Y", &Vec4f::Y,
			"Z", &Vec4f::Z,
			"W", &Vec4f::W,
			"length", &Vec4f::length,
			"normalize", &Vec4f::normalize,
			sol::meta_function::addition, [](const Vec4f& a, const Vec4f& b)
			{ return a + b; },
			sol::meta_function::multiplication, vec4_mult_overloads,
			sol::meta_function::subtraction, [](const Vec4f& a, const Vec4f& b)
			{ return a - b; },
			//sol::meta_function::unary_minus, [](Vec4f& v) -> Vec4f
			//{ return -v; },
			sol::meta_function::equal_to, [](Vec4f& a, Vec4f& b)
			{ return a == b; }
		);
	}

	void LuaLoader::bindAudioEngine()
	{
		auto lua = (*state)["Ak"].get_or_create<sol::table>();

		lua.new_usertype<Sound>(
			"Sound",
			sol::constructors<sol::types<>, sol::types<std::string>, sol::types<std::string, float, float>>(),
			"play", &Sound::play,
			"resume", &Sound::resume,
			"pause", &Sound::pause,
			"stop", &Sound::stop,
			"isPlaying", &Sound::isPlaying,
			"getPitch", &Sound::getPitch,
			"getGain", &Sound::getGain,
			"setPitch", &Sound::setPitch,
			"setGain", &Sound::setGain,
			"setDirection", &Sound::setDirection,
			"setPosition", &Sound::setPosition,
			"setVelocity", &Sound::setVelocity
		);
	}

	void LuaLoader::bindECS()
	{
		auto lua = (*state)["Ak"].get_or_create<sol::table>();

		lua.new_usertype<TransformAttribute>(
			"TransformAttribute",
			sol::constructors<sol::types<>>(),
			"position", &TransformAttribute::position,
			"rotation", &TransformAttribute::rotation,
			"scale", &TransformAttribute::scale
		);

		lua.new_usertype<AudioAttribute>(
			"AudioAttribute",
			sol::constructors<sol::types<>>(),
			"sound", &AudioAttribute::sound
		);

		lua.set_function("getAttribute", [](std::string_view attribute) -> sol::object
			{
				if(__entity == nullptr)
					return sol::lua_nil;
	
					TransformAttribute* trans = __entity->tryGetAttribute<TransformAttribute>();
				if(attribute == "transform" && trans != nullptr)
					return sol::make_object<std::reference_wrapper<TransformAttribute>>(*state, std::ref(*trans));

				AudioAttribute* audio = __entity->tryGetAttribute<AudioAttribute>();
				if(attribute == "audio" && audio != nullptr)
					return sol::make_object<std::reference_wrapper<AudioAttribute>>(*state, std::ref(*audio));

				return sol::lua_nil;
			});
	}

	void LuaLoader::bindSceneManager(SceneManager& manager)
	{
		auto lua = (*state)["Ak"].get_or_create<sol::table>();

		lua.set_function("switchToScene", [&](std::string scene) -> void
			{
				manager.switch_to_scene(std::move(scene));
			});
	}
}
