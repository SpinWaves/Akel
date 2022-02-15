// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 15/02/2022

#include <Core/core.h>

namespace Ak::Core
{
	void log::Init() // Remove ten days old files
	{
		lockThreads(mutex);

		std::string name = "";
		int date = 0;
		size_t finder = 0;

		for(auto& p: std::filesystem::directory_iterator(getLogsDirPath()))
		{
			name.clear();
			name.append(p.path().string(), getLogsDirPath().length(), p.path().string().length());

			if(name[0] == 's') // Looking for "session", the only alternative is ".gitignore" so it just needs to find if first char is "s"
			{
				if((finder = name.find("-")) != std::string::npos)
				{
					name.erase(name.begin(), name.begin() + finder + 1);	// Get day
					date = std::stoi(name);
					if((finder = name.find("-")) != std::string::npos)
					{
						name.erase(name.begin(), name.begin() + finder + 1);  // Get month
						if(Time::getCurrentTime().month != std::stoi(name))
							date -= 31;
					}
					if(date < Time::getCurrentTime().day - 10)
						std::filesystem::remove(p.path());
				}
			}
		}
		_out.open(getTime(getLogsDirPath()).c_str(), std::ios::app);
		if(_out.is_open())
		{
			_out << std::endl;
			_out.close();
		}

		unlockThreads(mutex);
	}

    void log::report(enum LogType type, std::string message, ...)
    {
		lockThreads(mutex);

		char buffer[message.length() + 255];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, std::move(message).c_str(), args);
		va_end(args);

		_out.open(getTime(getLogsDirPath()).c_str(), std::ios::app);
        if(_out.is_open())
		{
			switch(type)
			{
				case MESSAGE: std::cout << blue << "[Akel log Message] " << buffer << def << '\n'; _type = "Message: "; break;
				case WARNING: std::cout << magenta << "[Akel log Warning] " << buffer << def << '\n'; _type = "Warning: "; break;
				case ERROR: std::cout << red << "[Akel log Error] " << buffer << def << '\n'; _type = "Error: "; break;
				case FATAL_ERROR: std::cout << red << "[Akel log Fatal Error] " << buffer << def << '\n'; _type = "Fatal Error: "; break;

				default: break;
			}
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- " << _type << buffer << std::endl; // No need to flush, std::endl does it
			_out.close();
		}
        if(type == FATAL_ERROR)
        {
            std::set_terminate(TERMINATE);
			unlockThreads(mutex);
            std::terminate();
        }

		unlockThreads(mutex);
	}

    void log::report(std::string message, ...)
    {
		lockThreads(mutex);

		char buffer[message.length() + 255];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, message.c_str(), args);
		va_end(args);

		_out.open(getTime(getLogsDirPath()).c_str(), std::ios::app);
        if(_out.is_open())
		{
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- "<< buffer << std::endl;  // No need to flush, std::endl does it
			_out.close();
		}

		unlockThreads(mutex);
    }

    void log::TERMINATE() noexcept
    {
        std::cout << bg_red << "FATAL ERROR: emergency abortion program " << '\n' << "Trying to free all instanciated allocators... " << bg_def << std::endl;
		int allocators_leaks = 0;
		for(auto& elem : MemoryManager::accessToControlUnit()->jamStack)
		{
			if(!elem.expired())
			{
				elem.lock()->destroy();
				if(elem.lock()->is_init())
					allocators_leaks++;
			}
		}
		for(auto& elem : MemoryManager::accessToControlUnit()->fixedStack)
		{
			if(!elem.expired())
			{
				elem.lock()->destroy();
				if(elem.lock()->is_init())
					allocators_leaks++;
			}
		}
		_out.open(getTime(getLogsDirPath()).c_str(), std::ios::app);
		_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error: Trying to free all instanciated allocators..." << std::endl; // No need to flush, std::endl does it
		if(allocators_leaks == 0)
		{
        	std::cout << green << "All allocators have been correctly freed " << '\n' << "Program failed successfully ! " << def << std::endl;
			if(_out.is_open())
			{
				_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error: All allocators have been correctly freed" << std::endl; // No need to flush, std::endl does it
				_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error: Program failed successfully !" << std::endl; // No need to flush, std::endl does it
				_out.close();
			}
		}
		else
		{
			std::cout << bg_red << "Strong Fatal Error : Akel's core failed to free all instantiated allocators [" << allocators_leaks << " allocators leaked] " << bg_def << std::endl;
			if(_out.is_open())
			{
				_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error : Strong Fatal Error: Akel's core failed to free all instantiated allocators [" << allocators_leaks << " allocators leaked] " << std::endl; // No need to flush, std::endl does it
				_out.close();
			}
		}
        abort();
    }

    std::string log::getTime(std::string path)
    {
		__time time = Time::getCurrentTime();
		path.append("session-");
        path.append(std::to_string(time.day));
		path.append("-");
        path.append(std::to_string(time.month));
		path.append("-");
        path.append(std::to_string(time.year));
        path.append(".log");

        return std::move(path);
    }
}

namespace Ak
{
    void FatalError(std::string message, ...)
	{
		char buffer[message.length() + 255];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(FATAL_ERROR, buffer);
	}
    void Error(std::string message, ...)
	{
		char buffer[message.length() + 255];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(ERROR, buffer);
	}
    void Warning(std::string message, ...)
	{
		char buffer[message.length() + 255];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(WARNING, buffer);
	}
    void Message(std::string message, ...)
	{
		char buffer[message.length() + 255];
		va_list args;
		va_start(args, message);
		vsprintf(buffer, std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(MESSAGE, buffer);
	}
}
