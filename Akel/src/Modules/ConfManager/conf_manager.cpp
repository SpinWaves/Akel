// This file is a part of Akel
// CREATED : 10/08/2021
// UPDATED : 12/08/2021

#include <Modules/ConfManager/conf_manager.h>
#include <Core/core.h>

namespace Ak
{
    bool Conf_manager::load(const std::string& filename)
    {
        std::ifstream file(filename);
        if(!file.is_open())
        {
            Core::log::report(ERROR, "config file manager: unable to open " + filename);
            return false;
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

            if((equal_found = getter.find("=")) == std::string::npos && _warnings)
            {
                Core::log::report(WARNING, "config file manager: key declared without associated value (possible omission of \"=\")");
                _data[getter] = std::tuple<const char*, int, _type>(filename.c_str(), i, "");
                continue;
            }

            int space = 0;
            for(space = equal_found - 1; space >= 0; space--)
            {
                if(getter[space] != ' ')
                {
                    space++;
                    break;
                }
            }
            std::string key(getter.begin(), getter.begin() + space);

            for(space = equal_found + 1; space < getter.length(); space++)
            {
                if(getter[space] != ' ')
                    break;
            }
            std::string val(getter.begin() + space, getter.end());

            if(getter.find_first_not_of("0123456789.") == std::string::npos)
            {
                if(getter.find(".") != std::string::npos)
                {
                    _data[key] = std::tuple<const char*, int, _type>(filename.c_str(), i, std::stof(val));
                    continue;
                }
                    _data[key] = std::tuple<const char*, int, _type>(filename.c_str(), i, std::stoi(val));
                continue;
            }

            if(val == "true")
            {
                _data[key] = std::tuple<const char*, int, _type>(filename.c_str(), i, true);
                continue;
            }
            if(val == "false")
            {
                _data[key] = std::tuple<const char*, int, _type>(filename.c_str(), i, false);
                continue;
            }

            _data[key] = std::tuple<const char*, int, _type>(filename.c_str(), i, val);
        }

        file.close();

        return true;
    }

    bool Conf_manager::getBoolValue(const std::string& key)
    {
        if(_data.count(key))
        {
            if(std::holds_alternative<bool>(std::get<2>(_data[key])))
		      return std::get<bool>(std::get<2>(_data[key]));
            for(auto elem : Core::ProjectFile::getRam())
            {
                if(elem == _data[key])
                    return std::get<bool>(elem);
            }
        }
        return false;
    }
    int Conf_manager::getIntValue(const std::string& key)
    {
        if(_data.count(key))
        {
            if(std::holds_alternative<int>(std::get<2>(_data[key])))
		      return std::get<int>(std::get<2>(_data[key]));
            for(auto elem : Core::ProjectFile::getRam())
            {
                if(elem == _data[key])
                    return std::get<int>(elem);
            }
        }
        return 0;
    }
    float Conf_manager::getFloatValue(const std::string& key)
    {
        if(_data.count(key))
        {
            if(std::holds_alternative<float>(std::get<2>(_data[key])))
		      return std::get<float>(std::get<2>(_data[key]));
            for(auto elem : Core::ProjectFile::getRam())
            {
                if(elem == _data[key])
                    return std::get<float>(elem);
            }
        }
        return 0.0f;
    }
    std::string Conf_manager::getStringValue(const std::string& key)
    {
        if(_data.count(key))
        {
            if(std::holds_alternative<std::string>(std::get<2>(_data[key])))
		      return std::get<std::string>(std::get<2>(_data[key]));
            for(auto elem : Core::ProjectFile::getRam())
            {
                if(elem == _data[key])
                    return std::get<std::string>(elem);
            }
        }
        return "";
    }

    void Conf_manager::setStringValue(const std::string& key, const std::string& value)
    {
        if(!_data.count(key))
        {
            Core::log::report(ERROR, "config file manager: unable to modify string value of " + key + ", key not found");
            return;
        }

        std::fstream file(std::get<0>(_data[key]), std::ios::out | std::ios::in);
        if(!file.is_open())
            Core::log::report(ERROR, "config file manager: unable to modify string value of " + key + ", cannot open " + std::string(std::get<0>(_data[key])));

        std::string line;
        for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<1>(_data[key]))
                break;
        }

        size_t equal = 0;
        if((equal = line.find("=")) == std::string::npos)
        {
            line.erase(line.begin() + equal + 1, line.end());
            line.append(value);
        }
        else
            line.append(std::string(" = ") + value);

        _data[key] = std::tuple<const char*, int, _type>(std::get<0>(_data[key]), std::get<1>(_data[key]), value);

        file.close();
    }
    void Conf_manager::setIntValue(const std::string& key, const int value)
    {
        if(!_data.count(key))
        {
            Core::log::report(ERROR, "config file manager: unable to modify string value of " + key + ", key not found");
            return;
        }

        std::fstream file(std::get<0>(_data[key]), std::ios::out | std::ios::in);
        if(!file.is_open())
            Core::log::report(ERROR, "config file manager: unable to modify int value of " + key + ", cannot open " + std::string(std::get<0>(_data[key])));

        std::string line;
        for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<1>(_data[key]))
                break;
        }

        size_t equal = 0;
        if((equal = line.find("=")) == std::string::npos)
        {
            line.erase(line.begin() + equal + 1, line.end());
            line.append(std::to_string(value));
        }
        else
            line.append(std::string(" = ") + std::to_string(value));

        _data[key] = std::tuple<const char*, int, _type>(std::get<0>(_data[key]), std::get<1>(_data[key]), value);

        file.close();
    }
    void Conf_manager::setBoolValue(const std::string& key, const bool value)
    {
        std::string pass;
        if(value)
            pass = "true";
        else
            pass = "false";

        if(!_data.count(key))
        {
            Core::log::report(ERROR, "config file manager: unable to modify string value of " + key + ", key not found");
            return;
        }

        std::fstream file(std::get<0>(_data[key]), std::ios::out | std::ios::in);
        if(!file.is_open())
            Core::log::report(ERROR, "config file manager: unable to modify bool value of " + key + ", cannot open " + std::string(std::get<0>(_data[key])));

        std::string line;
        for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<1>(_data[key]))
                break;
        }

        size_t equal = 0;
        if((equal = line.find("=")) == std::string::npos)
        {
            line.erase(line.begin() + equal + 1, line.end());
            line.append(pass);
        }
        else
            line.append(std::string(" = ") + pass);

        _data[key] = std::tuple<const char*, int, _type>(std::get<0>(_data[key]), std::get<1>(_data[key]), value);

        file.close();
    }
    void Conf_manager::setFloatValue(const std::string& key, const float value)
    {
        if(!_data.count(key))
        {
            Core::log::report(ERROR, "config file manager: unable to modify string value of " + key + ", key not found");
            return;
        }

        std::fstream file(std::get<0>(_data[key]), std::ios::out | std::ios::in);
        if(!file.is_open())
            Core::log::report(ERROR, "config file manager: unable to modify float value of " + key + ", cannot open " + std::string(std::get<0>(_data[key])));

        std::string line;
        for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
        {
            if(i == std::get<1>(_data[key]))
                break;
        }
        size_t equal = 0;

        if((equal = line.find("=")) == std::string::npos)
        {
            line.erase(line.begin() + equal + 1, line.end());
            line.append(std::to_string(value));
        }
        else
            line.append(std::string(" = ") + std::to_string(value));

        _data[key] = std::tuple<const char*, int, _type>(std::get<0>(_data[key]), std::get<1>(_data[key]), value);

        file.close();
    }

    void Conf_manager::enableWarnings(bool set)
    {
        _warnings = set;
    }

    void Conf_manager::enableFileModifying(bool set)
    {
        _fileModifying = set;
    }
}
