// This file is a part of Akel
// CREATED : 10/08/2021
// UPDATED : 12/08/2021

#ifndef __AK_CONF_FILE_MANAGER__
#define __AK_CONF_FILE_MANAGER__

#include <Akpch.h>

namespace Ak
{
    class Conf_manager
    {
        public:
            Conf_manager() = default;
            static bool load(const std::string& filename);
            static bool getBoolValue(const std::string& key);
            static int getIntValue(const std::string& key);
            static float getFloatValue(const std::string& key);
            static std::string getStringValue(const std::string& key);

            static void setStringValue(const std::string& key, const std::string& value);
            static void setIntValue(const std::string& key, const int value);
            static void setBoolValue(const std::string& key, const bool value);
            static void setFloatValue(const std::string& key, const float value);

            static void enableWarnings(bool set = true);
            static void enableFileModifying(bool set = true);

        private:
            using _type = std::variant<std::string, int, bool, float>;
            inline static std::unordered_map<std::string, std::tuple<const char*, int, _type>> _data;
            // map construction: key            ->     <file,      line,              value>
            inline static bool _warnings = true;
            inline static bool _fileModifying = true;
    };
}

#endif // __AK_CONF_FILE_MANAGER__
