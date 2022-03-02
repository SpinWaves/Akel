// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2021
// Updated : 20/10/2021

#ifndef __AK_PROJECT_FILE__
#define __AK_PROJECT_FILE__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak::Core
{
    class ProjectFile
    {
        public:
            ProjectFile() = delete;

    		static void initProjFile();

            static void setDir(const std::string& dir);
            static void setName(const std::string& name);

            static bool getBoolValue(const std::string& key);
            static int getIntValue(const std::string& key);
            static float getFloatValue(const std::string& key);
            static std::string getStringValue(const std::string& key);

            static void setStringValue(const std::string& key, const std::string& value);
            static void setIntValue(const std::string& key, const int value);
            static void setBoolValue(const std::string& key, const bool value);
            static void setFloatValue(const std::string& key, const float value);

            ~ProjectFile() = delete;

        private:
            using _type = std::variant<std::string, int, bool, float>;
            // map construction:                 key         ->     <line, value>
            inline static std::unordered_map<std::string, std::tuple<int, _type>> _data;
            inline static std::string _name = "application";
            inline static std::string _dir = getMainDirPath();
    };
}

#endif // __AK_PROJECT_FILE__
