// This file is a part of Akel
// Authors : @kbz_8
// Created : 02/02/2024
// Updated : 11/02/2024

#include <Drivers/GLFW/GLFWModule.h>
#include <Core/Logs.h>

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

	GLFWModule& GLFWModule::Get()
	{
		Assert(s_instance != nullptr, "GLFWModule has not been instanciated");
		return *s_instance;
	}

	GLFWModule::~GLFWModule()
	{
		glfwTerminate();
		s_instance = nullptr;
	}
}
