// This file is a part of Akel
// CREATED : 12/08/2021
// UPDATED : 12/08/2021

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

            static void setDirFileProject(const std::string& dir);
    		static std::string getDirFileProject();
            static void setNameFileProject(const std::string& name);
    		static std::string getNameFileProject();
    		static void initProjFile();
            static void addToRam(std::variant<std::string, int, bool, float> text);
            static std::vector<std::variant<std::string, int, bool, float>> getRam();

            ~ProjectFile() = delete;

        private:
            inline static std::string _name = "application";
            inline static std::string _dir = getMainDirPath();
            inline static std::vector<std::variant<std::string, int, bool, float>> _ram;
    };
}

#endif // __AK_PROJECT_FILE__
