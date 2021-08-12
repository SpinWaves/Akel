// This file is a part of Akel
// CREATED : 12/08/2021
// UPDATED : 12/08/2021

#include <Core/core.h>

namespace Ak::Core
{
    void ProjectFile::setDirFileProject(const std::string& dir)
    {
        _dir = dir;
    }
	std::string ProjectFile::getDirFileProject()
    {
        return _dir;
    }
    void ProjectFile::setNameFileProject(const std::string& name)
    {
        _name = name;
    }
	std::string ProjectFile::getNameFileProject()
    {
        return _name;
    }
	void ProjectFile::initProjFile()
    {
		if(_dir.back() == '/')
			_dir.pop_back();

        std::cout << _dir + std::string("/") + _name + std::string(".akel") << std::endl;
		std::ofstream proj_file(_dir + std::string("/") + _name + std::string(".akel"));
		if(!proj_file.is_open())
			Core::log::report(FATAL_ERROR, "Application: unable to open/create project file in directory: " + _dir);

		proj_file << "# This file is an Akel project file. It contains configuration parameters for the engine." << '\n'
			      << "# DO NOT MODIFY IT, OTHERWISE YOU WILL GET BAD PERFORMANCES," << '\n'
				  << "# BAD MEMORY OPTIMISATION OR EVEN YOUR PROJECT WILL NOT WORK ANYMORE!" << '\n' << std::endl;
		proj_file.close();
    }

    void ProjectFile::addToRam(std::variant<std::string, int, bool, float> text)
    {
        _ram.push_back(text);
    }

    std::vector<std::variant<std::string, int, bool, float>> ProjectFile::getRam()
    {
        return _ram;
    }
}
