// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/05/2023
// Updated : 23/05/2023

#ifndef __AK_CORE_FILE_LOADER__
#define __AK_CORE_FILE_LOADER__

#include <Akpch.h>

namespace Ak
{
	bool loadJson(std::filesystem::path file, nlohmann::json& json);
	void writeJson(const nlohmann::json& data, std::filesystem::path file, bool raw_json = false);
}

#endif
