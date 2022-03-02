// This file is a part of Akel
// Author : @kbz_8
// CREATED : 03/04/2021
// UPDATED : 20/10/2021

#include <Core/core.h>

namespace Ak::Core
{
    std::string Paths::mainDirPath()
    {
        return MAIN_PATH;
    }
    std::string Paths::logDirPath()
    {
        return MAIN_PATH"Logs/";
    }
    std::string Paths::assetsDirPath()
    {
        return MAIN_PATH"Ressources/assets/";
    }
    std::string Paths::soundsDirPath()
    {
        return MAIN_PATH"Ressources/sounds/";
    }
    std::string Paths::fontsDirPath()
    {
        return MAIN_PATH"Ressources/fonts/";
    }
    std::string Paths::ressourcesDirPath()
    {
        return MAIN_PATH"Ressources/";
    }
    std::string Paths::shaderPath()
    {
        return MAIN_PATH"Akel/src/Shaders/";
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

    std::string getShaderPath()
    {
        return Paths::shaderPath();
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
