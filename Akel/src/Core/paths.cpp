// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 06/09/2021

#include <Core/core.h>

namespace Ak::Core
{
    void Paths::initPaths()
    {
        if(!_isInit)
        {
            path = std::filesystem::current_path();
            for(auto& dirs : std::filesystem::recursive_directory_iterator(path))
            {
                mainDir = dirs.path().string();
                std::size_t found = mainDir.rfind("Akel");
                if(found != std::string::npos)
                {
                    mainDir.erase(mainDir.begin() + found + 5, mainDir.end());
                    break;
                }
                mainDir = "Main path not found";
            }
            _isInit = true;
        }
    }
    std::string Paths::mainDirPath()
    {
        if(!_isInit)
            initPaths();
        return mainDir;
    }
    std::string Paths::logDirPath()
    {
        return mainDirPath() + "Logs/";
    }
    std::string Paths::assetsDirPath()
    {
        return mainDirPath() + "Ressources/assets/";
    }
    std::string Paths::soundsDirPath()
    {
        return mainDirPath() + "Ressources/sounds/";
    }
    std::string Paths::fontsDirPath()
    {
        return mainDirPath() + "Ressources/fonts/";
    }
    std::string Paths::ressourcesDirPath()
    {
        return mainDirPath() + "Ressources/";
    }

    void Paths::setLogsDir(std::string path)
    {
        logs = std::move(path);
    }
    void Paths::setFontsDir(std::string path)
    {
        fonts = std::move(path);
    }
    void Paths::setAssetsDir(std::string path)
    {
        assets = std::move(path);
    }
    void Paths::setSoundsDir(std::string path)
    {
        sounds = std::move(path);
    }

// =============================================================== //

    std::string getMainDirPath()
    {
        return Paths::mainDirPath();
    }
    std::string getAssetsDirPath()
    {
        return Paths::assetsDirPath();
    }

    std::string getLogsDirPath()
    {
        return Paths::logDirPath();
    }

    std::string getRessourcesDirPath()
    {
        return Paths::ressourcesDirPath();
    }
    std::string getSoundsDirPath()
    {
        return Paths::soundsDirPath();
    }

    std::string getFontsDirPath()
    {
        return Paths::fontsDirPath();
    }

    void setLogsDir(std::string path)
    {
        Paths::setLogsDir(std::move(path));
    }
    void setFontsDir(std::string path)
    {
        Paths::setFontsDir(std::move(path));
    }
    void setAssetsDir(std::string path)
    {
        Paths::setAssetsDir(std::move(path));
    }
    void setSoundsDir(std::string path)
    {
        Paths::setSoundsDir(std::move(path));
    }
}
