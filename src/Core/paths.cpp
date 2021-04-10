// This file is a part of AtlasEngine
// CREATED : 03/04/2021
// UPDATED : 04/04/2021

#include <Core/core.h>

namespace AE::Core
{
    std::filesystem::path path = std::filesystem::current_path();
    std::string getMainDirPath()
    {
        std::string mainPath;
        for(auto& dirs : std::filesystem::recursive_directory_iterator(path))
        {
            mainPath = dirs.path().string();
            std::size_t found = mainPath.rfind("AtlasEngine.h");
            if(found != std::string::npos)
            {
                mainPath.erase(mainPath.begin() + found - std::string("src/").length(), mainPath.end());
                return mainPath;
            }
        }
        return "Main path not found ";
    }

    std::string getAssetsDirPath()
    {
        return getMainDirPath() + "src/assets/";
    }

    std::string getLogsDirPath()
    {
        return getMainDirPath() + "Logs/";
    }
}
