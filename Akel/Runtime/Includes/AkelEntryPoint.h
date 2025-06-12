// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_ENTRY_POINT_H
#define AK_CORE_ENTRY_POINT_H

#include <Core/CompilationProfile.h>
#include <Core/Application.h>
#include <Core/EngineConfig.h>

// Setup functions defined by the user
extern void AkelSetupApplication(Ak::Application& app);
extern void AkelSetupEngineConfig(Ak::EngineConfig& config);

#if defined(AK_PLAT_WINDOWS)

	#include <Drivers/Windows/WindowsInstance.h>

	int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
	{
		Ak::WindowsInstance os;
		os.Init();

		Ak::EngineConfig config;
		AkelSetupEngineConfig(config);

		Ak::Application app(config);
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

		Ak::EngineConfig config;
		AkelSetupEngineConfig(config);

		Ak::Application app(config);
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
		os.Init(ac, av);

		Ak::EngineConfig config;
		AkelSetupEngineConfig(config);

		Ak::Application app(config);
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
