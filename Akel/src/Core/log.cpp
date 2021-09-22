// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 22/09/2021

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
				case MESSAGE: std::cout << blue << "Akel log: " << buffer << def << '\n'; _type = "Message: "; break;
				case WARNING: std::cout << magenta << "Akel log: " << buffer << def << '\n'; _type = "Warning: "; break;
				case ERROR: std::cout << red << "Akel log: " << buffer << def << '\n'; _type = "Error: "; break;
				case FATAL_ERROR: std::cout << red << "Akel log: " << buffer << def << '\n'; _type = "Fatal Error: "; break;

				default: break;
			}
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- " << _type << buffer << std::endl; // No need to flush, std::endl does it
			_out.close();
		}
        if(type == FATAL_ERROR)
        {
            std::set_terminate(TERMINATE);
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

    void log::TERMINATE()
    {
		for(auto elem : MemoryManager::accessToControlUnit()->jamStack)
		{
			elem->destroy();
		}
		for(auto elem : MemoryManager::accessToControlUnit()->fixedStack)
		{
			elem->destroy();
		}

        std::cout << bg_red << "EXIT FAILURE: emergency abortion program" << bg_def << std::endl;
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

        return path;
    }
}
