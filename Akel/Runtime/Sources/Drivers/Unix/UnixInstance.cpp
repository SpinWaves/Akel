// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/02/2024
// Updated : 11/02/2024

#include <Core/Application.h>
#include <Drivers/Unix/UnixInstance.h>

namespace Ak
{
	constexpr const int UNIX_PATH_MAX = 1024;

	void SignalsHandler([[maybe_unused]] int sig)
	{
		if(Application::IsInit())
			Application::Get().Quit();
	}

	void UnixInstance::Init(int ac, char** av)
	{
		m_av = av;
		m_ac = ac;
		OSInstance::SetInstance(this);
		signal(SIGINT, SignalsHandler);
		signal(SIGQUIT, SignalsHandler);
	}

	void UnixInstance::Shutdown()
	{
		OSInstance::SetInstance(nullptr);
	}

	std::filesystem::path UnixInstance::GetExecutablePath()
	{
		std::string path(UNIX_PATH_MAX, 0);
		if(std::filesystem::exists("/proc"))
		{
			int nchar = readlink("/proc/self/exe", path.data(), UNIX_PATH_MAX);
			if(nchar >= 0 && nchar < UNIX_PATH_MAX)
				return std::filesystem::path(path);
		}
		if(m_av == nullptr)
			return {};
		if(m_av[0] && realpath(m_av[0], path.data()))
			return std::filesystem::path(path);
		return {};
	}

	std::filesystem::path UnixInstance::GetCurrentWorkingDirectoryPath()
	{
		return std::filesystem::current_path();
	}

	bool UnixInstance::OpenURL([[maybe_unused]] const std::string& url)
	{
		using namespace std::literals;
		std::string command = "xdg-open"s + url;
		return std::system(command.c_str()) == 0;
	}

	void UnixInstance::Delay(std::uint32_t us)
	{
		struct timespec requested = { static_cast<time_t>(us / 1000000), (static_cast<long>(us) % 1000000) * 1000 };
		struct timespec remaining;
		while(nanosleep(&requested, &remaining) == -1)
		{
			requested.tv_sec  = remaining.tv_sec;
			requested.tv_nsec = remaining.tv_nsec;
		}
	}
}
