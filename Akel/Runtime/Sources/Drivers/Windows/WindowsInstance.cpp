// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 18/02/2024

#include <Core/CLI.h>
#include <Drivers/Windows/WindowsLibLoader.h>
#include <Drivers/Windows/WindowsInstance.h>

namespace Ak
{
	void WindowsInstance::Init()
	{
		OSInstance::SetInstance(this);
		OSInstance::SetLibLoader(new WindowsLibLoader);
		CommandLineInterface::Get().Feed(__argc, __argv);
	}

	void WindowsInstance::Shutdown()
	{
		OSInstance::SetInstance(nullptr);
		delete &OSInstance::GetLibLoader();
		OSInstance::SetLibLoader(nullptr);
	}

	[[nodiscard]]
	std::filesystem::path WindowsInstance::GetExecutablePath()
	{
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(NULL, path, MAX_PATH);

		std::string converted_string = std::filesystem::path(path).string();
		std::replace(converted_string.begin(), converted_string.end(), '\\', '/');

		return converted_string;
	}

	[[nodiscard]]
	std::filesystem::path WindowsInstance::GetCurrentWorkingDirectoryPath()
	{
		return std::filesystem::current_path();
	}

	bool WindowsInstance::OpenURL(const std::string& url)
	{
		ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

	void WindowsInstance::Delay(std::uint32_t us)
	{
		HANDLE timer;
		LARGE_INTEGER li;
		if(!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
			return;
		li.QuadPart = -(static_cast<std::uint64_t>(us) * 1000);
		if(SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE))
			WaitForSingleObject(timer, INFINITE);
		CloseHandle(timer);
	}

	bool WindowsInstance::SetTitleBarColor(Vec4f color, bool dark)
	{
		#if WINVER >= 0x0A00 && 0 // TODO
			HWND hwnd;

			COLORREF col = RGB(color.x * 255, color.y * 255, color.z * 255);

			COLORREF CAPTION_COLOR = col;
			COLORREF BORDER_COLOR  = 0x201e1e;

			DwmSetWindowAttribute(hwnd, 34 /*DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR*/, &BORDER_COLOR, sizeof(BORDER_COLOR));
			DwmSetWindowAttribute(hwnd, 35 /*DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR*/, &CAPTION_COLOR, sizeof(CAPTION_COLOR));
			SetWindowPos(hwnd, NULL, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE);
			return true
		#else
			return false;
		#endif
	}
}
