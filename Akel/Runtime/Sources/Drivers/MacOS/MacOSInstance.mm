// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 18/02/2024

#include <Core/CLI.h>
#include <Drivers/MacOS/MacOSLibLoader.h>
#include <Drivers/MacOS/MacOSInstance.h>

#import <Cocoa/Cocoa.h>

namespace Ak
{
	void MacOSInstance::Init(int ac, char** av)
	{
		OSInstance::SetInstance(this);
		OSInstance::SetLibLoader(new MacOSLibLoader);
		CommandLineInterface::Get().Feed(ac, av);
	}

	void MacOSInstance::Shutdown()
	{
		OSInstance::SetInstance(nullptr);
		delete &OSInstance::GetLibLoader();
		OSInstance::SetLibLoader(nullptr);
	}

	[[nodiscard]]
	std::filesystem::path MacOSInstance::GetExecutablePath()
	{
		std::uint32_t size = 0;
		_NSGetExecutablePath(nullptr, &size);

		std::vector<char> buffer;
		buffer.resize(size + 1);

		_NSGetExecutablePath(buffer.data(), &size);
		buffer[size] = '\0';

		if(!std::strrchr(buffer.data(), '/'))
			return std::filesystem::path{};
		return std::filesystem::path{buffer.data()};
	}

	[[nodiscard]]
	std::filesystem::path MacOSInstance::GetCurrentWorkingDirectoryPath()
	{
		return std::filesystem::current_path();
	}

	bool MacOSInstance::OpenURL([[maybe_unused]] const std::string& url)
	{
		using namespace std::literals;
		std::string command = "xdg-open"s + url;
		return std::system(command.c_str()) == 0;
	}

	void MacOSInstance::Delay(std::uint32_t us)
	{
		struct timespec requested = { static_cast<time_t>(us / 1000000), (static_cast<long>(us) % 1000000) * 1000 };
		struct timespec remaining;
		while(nanosleep(&requested, &remaining) == -1)
		{
			requested.tv_sec  = remaining.tv_sec;
			requested.tv_nsec = remaining.tv_nsec;
		}
	}

	bool MacOSInstance::SetTitleBarColor(Vec4f color, bool dark)
    {
		#if 0 // TODO
			NSWindow* window;
			window.titlebarAppearsTransparent = YES;
			//window.titleVisibility = NSWindowTitleHidden;

			NSColor *titleColour = [NSColor colorWithSRGBRed:colour.x green:colour.y blue:colour.z alpha:colour.w];
			window.backgroundColor = titleColour;
			if(dark)
				window.appearance = [NSAppearance appearanceNamed:NSAppearanceNameVibrantDark];
			else
				window.appearance = [NSAppearance appearanceNamed:NSAppearanceNameVibrantLight];
		#endif
		return true;
    }
}
