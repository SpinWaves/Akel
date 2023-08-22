// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 22/08/2023

#include <Core/core.h>
#include <Platform/messageBox.h>

namespace Ak::Core
{
	void log::init(std::filesystem::path path) // Removes ten days old files
	{
		std::lock_guard<std::mutex> watchdog(mutex);

		std::string name = "";
		int date = 0;
		size_t finder;

		path.remove_filename();
		path /= ".akel_logs/";
		_log_dir = path;
		if(!std::filesystem::exists(_log_dir))
		{
			std::filesystem::create_directory(_log_dir);
			return;
		}

		for(auto& p: std::filesystem::directory_iterator(_log_dir))
		{
			name.clear();
			name.append(p.path().string(), _log_dir.string().length(), p.path().string().length());

			if(name[0] == 's')
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
		_out.open(getTime().c_str(), std::ios::app);
		if(_out.is_open())
		{
			_out << std::endl;
			_out.close();
		}
	}

    void log::report(enum LogType type, std::string message, ...)
    {
		#ifdef AK_RELEASE
			if(type == DEBUGLOG)
				return;
		#endif
		std::lock_guard<std::mutex> watchdog(mutex);

		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		#ifdef AK_RELEASE
			if(type != STRONG_WARNING && type != WARNING)
				messageBox(type, "Akel logs recieved a report", buffer, false);
		#endif

		_out.open(getTime().c_str(), std::ios::app);
        if(_out.is_open())
		{
			switch(type)
			{
				case DEBUGLOG: std::cout << blue << "[Akel log Debug] " << buffer << def << '\n'; _type = "Debug: "; break;
				case MESSAGE: std::cout << blue << "[Akel log Message] " << buffer << def << '\n'; _type = "Message: "; break;
				case WARNING:
				{	
					if(getMainAppProjectFile().archive()["enable_warning_console_message"])
						std::cout << magenta << "[Akel log Warning] " << buffer << def << '\n';
					_type = "Warning: ";
					break;
				}
				case STRONG_WARNING: std::cout << yellow << "[Akel log Strong Warning] " << buffer << def << '\n'; _type = "Strong Warning: "; break;
				case ERROR: std::cerr << red << "[Akel log Error] " << buffer << def << '\n'; _type = "Error: "; break;
				case FATAL_ERROR: std::cerr << red << "[Akel log Fatal Error] " << buffer << def << '\n'; _type = "Fatal Error: "; break;

				default: break;
			}
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- " << _type << buffer << std::endl; // No need to flush, std::endl does it
		}
        if(type == FATAL_ERROR)
        {
	        std::cout << bg_red << "FATAL ERROR: emergency abortion program " << '\n' << "Trying to free all instanciated allocators... " << std::endl << bg_def;
			int allocators_leaks = 0;
			if(MemoryManager::is_init())
			{
				for(auto& elem : MemoryManager::accessToControlUnit()->jamStack)
				{
					if(!elem.expired())
					{
						elem.lock()->destroy();
						if(elem.lock()->isInit())
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
			}
			_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error: Trying to free all instanciated allocators..." << std::endl; // No need to flush, std::endl does it
			if(allocators_leaks == 0)
			{
	        	std::cout << green << "All allocators have been correctly freed " << '\n' << "Program failed successfully ! " << def << std::endl;
				if(_out.is_open())
				{
					_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error: All allocators have been correctly freed" << std::endl; // No need to flush, std::endl does it
					_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error: Program failed successfully !" << std::endl; // No need to flush, std::endl does it
				}
			}
			else
			{
				std::cout << bg_red << "Strong Fatal Error : Akel's core failed to free all instantiated allocators [" << allocators_leaks << " allocators leaked] " << bg_def << std::endl;
				if(_out.is_open())
					_out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- Fatal Error : Strong Fatal Error: Akel's core failed to free all instantiated allocators [" << allocators_leaks << " allocators leaked] " << std::endl; // No need to flush, std::endl does it
			}

			_out.close();
			std::exit(0);
        }
		_out.close();
	}

    void log::report(std::string message, ...)
    {
		std::lock_guard<std::mutex> watchdog(mutex);

		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		_out.open(getTime().c_str(), std::ios::app);
        if(_out.is_open())
		{
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- "<< buffer << std::endl;  // No need to flush, std::endl does it
			_out.close();
		}
    }

    std::string log::getTime()
    {
		__time time = Time::getCurrentTime();
		std::string copy = _log_dir.string();
		copy.append("session-");
        copy.append(std::to_string(time.day));
		copy.append("-");
        copy.append(std::to_string(time.month));
		copy.append("-");
        copy.append(std::to_string(time.year));
        copy.append(".akel.log");
        
		return copy;
    }
}

namespace Ak
{
    void FatalError(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(FATAL_ERROR, buffer);
	}
    void Error(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(ERROR, buffer);
	}
    void Warning(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(WARNING, buffer);
	}
    void Strong_Warning(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(STRONG_WARNING, buffer);
	}
    void Message(std::string message, ...)
	{
		std::string buffer(message.length() + 1024, 0);
		va_list args;
		va_start(args, message);
		vsprintf(buffer.data(), std::move(message).c_str(), args);
		va_end(args);

		Core::log::report(MESSAGE, buffer);
	}
}
