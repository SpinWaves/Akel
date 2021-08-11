// This file is a part of Akel
// CREATED : 10/08/2021
// UPDATED : 11/08/2021

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
        size_t com_found = 0
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
                _data[filename.c_str()][key] = std::pair<int, std::variant<std::string, bool, float, int>(i, "");
                continue;
            }

            std::string key(getter.begin(), getter.begin() + equal_found);
            std::string val(getter.begin() + equal_found, getter.end());

            if(getter.find_first_not_of("0123456789.") == std::string::npos)
            {
                if(getter.find(".") != std::string::npos)
                {
                    _data[filename.c_str()][key] = std::pair<int, std::variant<std::string, bool, float, int>(i, std::stof(val));
                    continue;
                }
                _data[filename.c_str()][key] = std::pair<int, std::variant<std::string, bool, float, int>(i, std::stoi(val));
                continue;
            }

            if(val == "true")
                _data[filename.c_str()][key] = std::pair<int, std::variant<std::string, bool, float, int>(i, true);
            if(val == "false")
                _data[filename.c_str()][key] = std::pair<int, std::variant<std::string, bool, float, int>(i, false);

            _data[filename.c_str()][key] = std::pair<int, std::variant<std::string, bool, float, int>(i, val);
        }

        file.close();

        return true;
    }

    bool Conf_manager::getBoolValue(const std::string& key)
    {
        for(auto elem : _data)
        {
            if(elem.second.count(key) && std::holds_alternative<bool>(elem.second[key].second))
    		      return std::get<bool>(elem.second[key].second);
        }
        return false;
    }
    int Conf_manager::getIntValue(const std::string& key)
    {
        for(auto elem : _data)
        {
            if(elem.second.count(key) && std::holds_alternative<int>(elem.second[key].second))
    		      return std::get<int>(elem.second[key].second);
        }
        return 0;
    }
    float Conf_manager::getFloatValue(const std::string& key)
    {
        for(auto elem : _data)
        {
            if(elem.second.count(key) && std::holds_alternative<float>(elem.second[key].second))
    		      return std::get<float>(elem.second[key].second);
        }
        return 0.0f;
    }
    std::string Conf_manager::getStringValue(const std::string& key)
    {
        for(auto elem : _data)
        {
            if(elem.second.count(key) && std::holds_alternative<std::string>(elem.second[key]))
    		      return std::get<std::string>(elem.second[key]);
        }
        return "";
    }

    void Conf_manager::setStringValue(const std::string& key, const std::string& value)
    {
        for(auto elem : _data)
        {
            if(!elem.second.count(key))
                continue;

            std::fstream file(elem.first, std::ios::out | std::ios::in);
            if(!file.is_open())
                Core::log::report(ERROR, "config file manager: unable to modify string value of " + key + ", cannot open " + std::string(elem.first));

            std::string line;
            for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
            {
                if(i == elem.second[key].first)
                    break;
            }

            size_t equal = 0;
            if((equal = line.find("=")) == std::string::npos)
            {
                line.erase(line.begin() + equal + 1, line.end());
                line.append(value);
            }
            else
                line.append(" = " + value);

            elem.second[key].second = value;

            file.close();
            return;
        }
        Core::log::report(ERROR, "config file manager: unable to modify string value of" + key + ", key not found");
    }
    void Conf_manager::setIntValue(const std::string& key, const int value)
    {
        for(auto elem : _data)
        {
            if(!elem.second.count(key))
                continue;

            std::fstream file(elem.first, std::ios::out | std::ios::in);
            if(!file.is_open())
                Core::log::report(ERROR, "config file manager: unable to modify int value of " + key + ", cannot open " + std::string(elem.first));

            std::string line;
            for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
            {
                if(i == elem.second[key].first)
                    break;
            }

            size_t equal = 0;
            if((equal = line.find("=")) == std::string::npos)
            {
                line.erase(line.begin() + equal + 1, line.end());
                line.append(std::to_string(value));
            }
            else
                line.append(" = " + std::to_string(value));

            elem.second[key].second = value;

            file.close();
            return;
        }
        Core::log::report(ERROR, "config file manager: unable to modify int value of" + key + ", key not found");
    }
    void Conf_manager::setBoolValue(const std::string& key, const bool value)
    {
        std::string pass;
        if(value)
            pass = "true";
        else
            pass = "false";

        for(auto elem : _data)
        {
            if(!elem.second.count(key))
                continue;

            std::fstream file(elem.first, std::ios::out | std::ios::in);
            if(!file.is_open())
                Core::log::report(ERROR, "config file manager: unable to modify bool value of " + key + ", cannot open " + std::string(elem.first));

            std::string line;
            for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
            {
                if(i == elem.second[key].first)
                    break;
            }

            size_t equal = 0;
            if((equal = line.find("=")) == std::string::npos)
            {
                line.erase(line.begin() + equal + 1, line.end());
                line.append(pass);
            }
            else
                line.append(" = " + pass);

            elem.second[key].second = value;

            file.close();
            return;
        }
        Core::log::report(ERROR, "config file manager: unable to modify bool value of" + key + ", key not found");
    }
    void Conf_manager::setFloatValue(const std::string& key, const float value)
    {
        for(auto elem : _data)
        {
            if(!elem.second.count(key))
                continue;

            std::fstream file(elem.first, std::ios::out | std::ios::in);
            if(!file.is_open())
                Core::log::report(ERROR, "config file manager: unable to modify float value of " + key + ", cannot open " + std::string(elem.first));

            std::string line;
            for(int i = 0; getline(file, line); i++) // Acces to key line (seekg have problems with files opened in text mode)
            {
                if(i == elem.second[key].first)
                    break;
            }

            size_t equal = 0;
            if((equal = line.find("=")) == std::string::npos)
            {
                line.erase(line.begin() + equal + 1, line.end());
                line.append(std::to_string(value));
            }
            else
                line.append(" = " + std::to_string(value));

            elem.second[key].second = value;

            file.close();
            return;
        }
        Core::log::report(ERROR, "config file manager: unable to modify float value of" + key + ", key not found");
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
