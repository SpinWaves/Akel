// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 07/09/2021

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
        static std::string ressourcesDirPath();
        static std::string soundsDirPath();
        static std::string fontsDirPath();
        static void setLogsDir(std::string path);
        static void setFontsDir(std::string path);
        static void setAssetsDir(std::string path);
        static void setSoundsDir(std::string path);

        ~Paths() = delete;

        private:
            inline static std::string mainDir;
            inline static std::filesystem::path path;
            inline static bool _isInit = false;
            inline static std::string logs;
            inline static std::string assets;
            inline static std::string sounds;
            inline static std::string fonts;
    };
    std::string getMainDirPath();
    std::string getAssetsDirPath();
    std::string getLogsDirPath();
    std::string getRessourcesDirPath();
    std::string getSoundsDirPath();
    std::string getFontsDirPath();

    void setLogsDir(std::string path);
    void setFontsDir(std::string path);
    void setAssetsDir(std::string path);
    void setSoundsDir(std::string path);
}

#endif // __AK_PATHS__
