// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 04/08/2021

#include <Core/core.h>

namespace Ak::Core
{
    std::filesystem::path path = std::filesystem::current_path();
    std::string getMainDirPath()
    {
        std::string mainPath;
        for(auto& dirs : std::filesystem::recursive_directory_iterator(path))
        {
            mainPath = dirs.path().string();
            std::size_t found = mainPath.rfind("Akel");
            if(found != std::string::npos)
            {
                mainPath.erase(mainPath.begin() + found + 5, mainPath.end());
                return mainPath;
            }
        }
        return "Main path not found";
    }

    std::string getAssetsDirPath()
    {
        return getMainDirPath() + "Ressources/";
    }

    std::string getLogsDirPath()
    {
        return getMainDirPath() + "Logs/";
    }
}
