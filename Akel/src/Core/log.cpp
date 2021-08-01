// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 01/08/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak::Core
{
	void log::Init() // Remove ten days old files
	{
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
	}

    void log::report(enum LogType type, std::string message)
    {
		_out.open(getTime(getLogsDirPath()).c_str(), std::ios::app);
        if(_out.is_open())
		{
			switch(type)
			{
				case MESSAGE: std::cout << blue << "Akel log: " << message << def << '\n'; _type = "Message: "; break;
				case WARNING: std::cout << magenta << "Akel log: " << message << def << '\n'; _type = "Warning: "; break;
				case ERROR: std::cout << red << "Akel log: " << message << def << '\n'; _type = "Error: "; break;
				case FATAL_ERROR: std::cout << red << "Akel log: " << message << def << '\n'; _type = "Fatal Error: "; break;

				default: break;
			}
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- " << _type << message << std::endl; // No need to flush, std::endl does it
			_out.close();
		}
        if(type == FATAL_ERROR)
        {
            std::set_terminate(TERMINATE);
            std::terminate();
        }
	}

    void log::report(std::string message)
    {
		_out.open(getTime(getLogsDirPath()).c_str(), std::ios::app);
        if(_out.is_open())
		{
            _out << (int)Time::getCurrentTime().hour << ":" << (int)Time::getCurrentTime().min << " ---- "<< message << std::endl;  // No need to flush, std::endl does it
			_out.close();
		}
    }

    void log::TERMINATE()
    {
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
