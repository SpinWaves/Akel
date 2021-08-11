// This file is a part of Akel
// CREATED : 10/08/2021
// UPDATED : 11/08/2021

#ifndef __AK_CONF_FILE_MANAGER__
#define __AK_CONF_FILE_MANAGER__

#include <Akpch.h>

namespace Ak
{
    class Conf_manager
    {
        public:
            Conf_manager() = default;
            bool load(const std::string& filename);
            bool getBoolValue(const std::string& key);
            int getIntValue(const std::string& key);
            float getFloatValue(const std::string& key);
            std::string getStringValue(const std::string& key);

            void setStringValue(const std::string& key, const std::string& value);
            void setIntValue(const std::string& key, const int value);
            void setBoolValue(const std::string& key, const bool value);
            void setFloatValue(const std::string& key, const float value);

            void enableWarnings(bool set = true);
            void enableFileModifying(bool set = true);

        private:
            std::unordered_map<const char*, std::unordered_map<std::string, std::pair<int, std::variant<std::string, int, bool, float>>>> _data;
            bool _warnings = true;
            bool _fileModifying = true;
    };
}

#endif // __AK_CONF_FILE_MANAGER__
