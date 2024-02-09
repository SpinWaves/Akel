// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 09/02/2024

#ifndef __AK_CORE_ENTRY_POINT__
#define __AK_CORE_ENTRY_POINT__

#include <Core/CompilationProfile.h>
#include <Core/Application.h>

extern void AkelSetupApplication(Ak::Application& app);

#if defined(AK_PLAT_WINDOWS)

	#include <Drivers/Windows/WindowsInstance.h>

	int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
	{
		Ak::WindowsInstance os;
		os.Init();

		Ak::Application app;
		AkelSetupApplication(app);

		app.Run();

		app.ShutdownAllEngineModules();

		os.Shutdown();
		return 0;
	}

#elif defined(AK_PLAT_UNIX)

	#include <Drivers/Unix/UnixInstance.h>

	int main(int ac, char** av)
	{
		Ak::UnixInstance os;
		os.Init(ac, av);

		Ak::Application app;
		AkelSetupApplication(app);

		app.Run();

		app.ShutdownAllEngineModules();

		os.Shutdown();
		return 0;
	}

#elif defined(AK_PLAT_MACOS)

	#include <Drivers/MacOS/MacOSInstance.h>

	int main(int ac, char** av)
	{
		Ak::MacOSInstance os;
		os.Init();

		Ak::Application app;
		AkelSetupApplication(app);

		app.Run();

		app.ShutdownAllEngineModules();

		os.Shutdown();
		return 0;
	}

#else
	#error "unknown platform"
#endif

#endif
