// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 12/08/2021

#include <Core/core.h>

namespace Ak::Core
{
    void Paths::initPaths()
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
    std::string Paths::mainDirPath()
    {
        if(!_isInit)
            initPaths();
        return mainDir;
    }
    std::string Paths::logDirPath()
    {
        return mainDir + "Logs/";
    }
    std::string Paths::assetsDirPath()
    {
        return mainDir + "Ressources/";
    }

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
}
