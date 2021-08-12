// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 12/08/2021

#ifndef __AK_PATHS__
#define __AK_PATHS__

#include <Akpch.h>

namespace Ak::Core
{
    struct Paths
    {
        Paths() = delete;

        static void initPaths();
        static std::string mainDirPath();
        static std::string logDirPath();
        static std::string assetsDirPath();

        ~Paths() = delete;

        private:
            inline static std::string mainDir;
            inline static std::filesystem::path path;
            inline static bool _isInit = false;
    };
    std::string getMainDirPath();
    std::string getAssetsDirPath();
    std::string getLogsDirPath();
}

#endif // __AK_PATHS__
