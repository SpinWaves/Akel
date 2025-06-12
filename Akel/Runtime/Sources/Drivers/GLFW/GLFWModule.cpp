// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Drivers/GLFW/GLFWModule.h>
#include <Core/Logs.h>
#include <Config.h>

namespace Ak
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		Error("GLFW (%) : %", error, description);
	}

	GLFWModule* GLFWModule::s_instance = nullptr;

	GLFWModule::GLFWModule() : Module("GLFWModule")
	{
		if(s_instance != nullptr)
			FatalError("only one instance of GLFWModule can exist at a given time");
		if(!glfwInit())
			FatalError("GLFW error : unable to init all subsystems");
		s_instance = this;
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	std::string GLFWModule::GetEngineModuleVersion()
	{
		return AKEL_VERSION;
	}

	GLFWModule& GLFWModule::Get()
	{
		Assert(s_instance != nullptr, "GLFWModule has not been instanciated");
		return *s_instance;
	}

	GLFWModule::~GLFWModule()
	{
		Module::~Module();
		glfwTerminate();
		s_instance = nullptr;
	}
}
