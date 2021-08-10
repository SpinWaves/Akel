// This file is a part of Akel
// CREATED : 10/08/2021
// UPDATED : 10/08/2021

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

        file.close();

        return true;
    }

    bool Conf_manager::getBoolValue(const std::string& key) {}
    int Conf_manager::getIntValue(const std::string& key) {}
    float Conf_manager::getFloatValue(const std::string& key) {}
    std::string Conf_manager::getStringValue(const std::string& key) {}

    void Conf_manager::setStringValue(const std::string& key, const std::string& value) {}
    void Conf_manager::setIntValue(const std::string& key, const int value) {}
    void Conf_manager::setBoolValue(const std::string& key, const bool value) {}
    void Conf_manager::setFloatValue(const std::string& key, const float value) {}
}
