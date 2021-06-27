// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 27/06/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak::Core
{
    void log::report(enum LogType type, std::string message)
    {
		_out.open(getTime(type, getLogsDirPath()).c_str(), std::ios::app);
        if(_out.is_open())
		{
            _out << _now->tm_hour << ":" << _now->tm_min << " ---- " << message << std::endl;
			_out.flush();
			_out.close();
		}
        if(type == FATAL_ERROR)
        {
            std::set_terminate(TERMINATE);
            std::terminate();
        }
    }

    void log::TERMINATE()
    {
        std::cout << bg_red << "EXIT FAILURE: emergency abortion program" << bg_def << std::endl;
        abort();
    }

    std::string log::getTime(enum LogType type, std::string path)
    {
		std::time_t t = std::time(0);
		_now = std::localtime(&t);

		path.append("session-");
        path.append(std::to_string(_now->tm_mday));
		path.append("-");
        path.append(std::to_string(_now->tm_mon + 1));
		path.append("-");
        path.append(std::to_string(_now->tm_year + 1900));
        path.append(".log");

        return path;
    }
}
