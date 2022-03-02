// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 07/11/2021

#include <Core/core.h>

#define __FILEPATH _dir + _name + std::string(".akel")

namespace Ak::Core
{
	void ProjectFile::initProjFile()
    {
		if(_dir.back() != '/')
			_dir.push_back('/');
        std::filesystem::path f(__FILEPATH);
        if(!std::filesystem::exists(f))
        {
    		std::ofstream proj_file(__FILEPATH);
    		if(!proj_file.is_open())
    			Core::log::report(FATAL_ERROR, "Application: unable to open/create project file in directory: " + _dir);

            std::string useMemMan = "false";
            if(MemoryManager::isMemoryManagerUsed())
                useMemMan = "true";

    		proj_file << "# This file is an Akel project file. It contains configuration parameters for the engine." << '\n'
    			      << "# DO NOT MODIFY IT, OTHERWISE YOU WILL GET BAD PERFORMANCES," << '\n'
    				  << "# BAD MEMORY OPTIMISATION OR EVEN YOUR PROJECT WILL NOT WORK ANYMORE!" << '\n' << std::endl;
    		proj_file.close();
        }

        std::ifstream file(__FILEPATH);
        if(!file.is_open())
        {
            Core::log::report(ERROR, "config file manager: unable to open " + _dir + _name + std::string(".akel"));
            return;
        }

        std::string getter;
        size_t com_found = 0;
        size_t equal_found = 0;
        for(int i = 0; std::getline(file, getter); i++)
        {
            if((com_found = getter.find("#")) != std::string::npos)
                getter.erase(getter.begin() + com_found, getter.end());

            if(getter.empty())
                continue;

            if((equal_found = getter.find("=")) == std::string::npos)
            {
                _data[getter] = std::tuple<int, _type>(i, "");
                continue;
            }

            std::string key(getter.begin(), getter.begin() + equal_found - 1);
            std::string val(getter.begin() + equal_found + 2, getter.end());

            if(getter.find_first_not_of("0123456789.") == std::string::npos)
            {
                if(getter.find(".") != std::string::npos)
                {
                    _data[key] = std::tuple<int, _type>(i, std::stof(val));
                    continue;
                }
                    _data[key] = std::tuple<int, _type>(i, std::stoi(val));
                continue;
            }

            if(val == "true")
            {
                _data[key] = std::tuple<int, _type>(i, true);
                continue;
            }
            if(val == "false")
            {
                _data[key] = std::tuple<int, _type>(i, false);
                continue;
            }

            _data[key] = std::tuple<int, _type>(i, val);
        }

        file.close();
    }

    void ProjectFile::setDir(const std::string& dir)
    {
        _dir = dir;
    }
    void ProjectFile::setName(const std::string& name)
    {
        _name = name;
    }

    bool ProjectFile::getBoolValue(const std::string& key)
    {
        if(std::holds_alternative<bool>(std::get<1>(_data[key])))
	      return std::get<bool>(std::get<1>(_data[key]));
        return false;
    }
    int ProjectFile::getIntValue(const std::string& key)
    {
        if(std::holds_alternative<int>(std::get<1>(_data[key])))
	      return std::get<int>(std::get<1>(_data[key]));
        return 0;
    }
    float ProjectFile::getFloatValue(const std::string& key)
    {
        if(std::holds_alternative<float>(std::get<1>(_data[key])))
	      return std::get<float>(std::get<1>(_data[key]));
        return 0.0f;
    }
    std::string ProjectFile::getStringValue(const std::string& key)
    {
        if(std::holds_alternative<std::string>(std::get<1>(_data[key])))
	      return std::get<std::string>(std::get<1>(_data[key]));
        return "";
    }

    void ProjectFile::setStringValue(const std::string& key, const std::string& value)
    {
        std::fstream file(__FILEPATH, std::fstream::in | std::fstream::out | std::fstream::ate);
        if(!file.is_open())
            Core::log::report(ERROR, "Project file manager: unable to modify a project file, cannot open " + __FILEPATH);

        std::string line;
        if(!_data.count(key))
        {
            file << key << " = " << value << std::endl;
            int lines = 0;
            while(getline(file, line))
               lines++;
            file.close();
            _data[key] = std::tuple<int, _type>(lines - 1, value); // lines - 1 because we ended file with std::endl so it makes a new line
            return;
        }

        std::ofstream newFile(_dir + std::string("temp.akel"));
        if(!newFile.is_open())
        {
            Core::log::report(WARNING, "Project file manager: unable to modify project file: unable to create new file");
            return;
        }

		file.seekg(0, file.beg);

        for(int i = 0; getline(file, line); i++) // Access to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<0>(_data[key]))
            {
                size_t equal = 0;
                if((equal = line.find("=")) != std::string::npos)
                {
                    line.erase(line.begin() + equal + 2, line.end());
                    line.append(value);
                }
                else
                    line.append(std::string(" = ") + value);
            }
            newFile << line << '\n';
			line.clear();
        }

        file.close();
        newFile.close();

		std::filesystem::remove(__FILEPATH);
        std::filesystem::rename(_dir + "temp.akel", __FILEPATH);

        _data[key] = std::tuple<int, _type>(std::get<0>(_data[key]), value);

    }

    void ProjectFile::setIntValue(const std::string& key, const int value)
    {
        std::fstream file(__FILEPATH, std::fstream::in | std::fstream::out | std::fstream::ate);
        if(!file.is_open())
            Core::log::report(ERROR, "Project file manager: unable to modify a project file, cannot open " + __FILEPATH);

        std::string line;
        if(!_data.count(key))
        {
            file << key << " = " << value << std::endl;
            int lines = 0;
            while(std::getline(file, line))
               lines++;
            file.close();
            _data[key] = std::tuple<int, _type>(lines - 1, value); // lines - 1 because we ended file with std::endl so it makes a new line
            return;
        }

        std::ofstream newFile(_dir + std::string("temp.akel"));
        if(!newFile.is_open())
        {
            Core::log::report(WARNING, "Project file manager: unable to modify project file: unable to create new file");
            return;
        }

		file.seekg(0, file.beg);

        for(int i = 0; std::getline(file, line); i++) // Access to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<0>(_data[key]))
            {
                size_t equal = 0;
                if((equal = line.find("=")) != std::string::npos)
                {
                    line.erase(line.begin() + equal + 2, line.end());
                    line.append(std::to_string(value));
                }
                else
                    line.append(std::string(" = ") + std::to_string(value));
            }
        	newFile << line << '\n';
			line.clear();
        }

        file.close();
        newFile.close();

		std::filesystem::remove(__FILEPATH);
        std::filesystem::rename(_dir + "temp.akel", __FILEPATH);

        _data[key] = std::tuple<int, _type>(std::get<0>(_data[key]), value);
    }

    void ProjectFile::setBoolValue(const std::string& key, const bool value)
    {
        std::string pass;
        if(value)
            pass = "true";
        else
            pass = "false";

        std::fstream file(__FILEPATH, std::fstream::in | std::fstream::out | std::fstream::ate);
        if(!file.is_open())
            Core::log::report(ERROR, "Project file manager: unable to modify a project file, cannot open " + __FILEPATH);

        std::string line;
        if(!_data.count(key))
        {
            file << key << " = " << pass << std::endl;
            int lines = 0;
            while(getline(file, line))
               lines++;
            file.close();
            _data[key] = std::tuple<int, _type>(lines - 1, value); // lines - 1 because we ended file with std::endl so it makes a new line
            return;
        }

        std::ofstream newFile(_dir + std::string("temp.akel"));
        if(!newFile.is_open())
        {
            Core::log::report(WARNING, "Project file manager: unable to modify project file: unable to create new file");
            return;
        }

		file.seekg(0, file.beg);

        for(int i = 0; getline(file, line); i++) // Access to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<0>(_data[key]))
            {
                size_t equal = 0;
                if((equal = line.find("=")) != std::string::npos)
                {
                    line.erase(line.begin() + equal + 2, line.end());
                    line.append(pass);
                }
                else
                    line.append(std::string(" = ") + pass);
            }
            newFile << line << '\n';
			line.clear();
        }

        file.close();
        newFile.close();

		std::filesystem::remove(__FILEPATH);
        std::filesystem::rename(_dir + "temp.akel", __FILEPATH);

        _data[key] = std::tuple<int, _type>(std::get<0>(_data[key]), value);
    }

    void ProjectFile::setFloatValue(const std::string& key, const float value)
    {
        std::fstream file(__FILEPATH, std::fstream::in | std::fstream::out | std::fstream::ate);
        if(!file.is_open())
            Core::log::report(ERROR, "Project file manager: unable to modify a project file, cannot open " + __FILEPATH);

        std::string line;
        if(!_data.count(key))
        {
            file << key << " = " << value << std::endl;
            int lines = 0;
            while(getline(file, line))
               lines++;
            file.close();
            _data[key] = std::tuple<int, _type>(lines - 1, value); // lines - 1 because we ended file with std::endl so it makes a new line
            return;
        }

        std::ofstream newFile(_dir + std::string("temp.akel"));
        if(!newFile.is_open())
        {
            Core::log::report(WARNING, "Project file manager: unable to modify project file: unable to create new file");
            return;
        }

		file.seekg(0, file.beg);

        for(int i = 0; getline(file, line); i++) // Access to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<0>(_data[key]))
            {
                size_t equal = 0;
                if((equal = line.find("=")) != std::string::npos)
                {
                    line.erase(line.begin() + equal + 2, line.end());
                    line.append(std::to_string(value));
                }
                else
                    line.append(std::string(" = ") + std::to_string(value));
            }
            newFile << line << '\n';
			line.clear();
        }

        file.close();
        newFile.close();

		std::filesystem::remove(__FILEPATH);
        std::filesystem::rename(_dir + "temp.akel", __FILEPATH);

        _data[key] = std::tuple<int, _type>(std::get<0>(_data[key]), value);
    }
}
