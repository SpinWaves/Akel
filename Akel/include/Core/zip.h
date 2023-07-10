// This file is a part of Akel
// Authors : @kbz_8
// Created : 10/07/2023
// Updated : 10/07/2023

#ifndef __AK_ZIP__
#define __AK_ZIP__

#include <Akpch.h>

namespace Ak
{
	class AK_API Zip
	{
		public:
			Zip(const std::filesystem::path& path);
			std::string getFileFromZip(const std::string& filename);
			bool writeFileToZip(const std::filesystem::path& path, const std::string& filename);
			bool writeFileDataToZip(const std::string& path, const std::string& filedata);
			~Zip();

		private:
			zip_t* _zip = nullptr;
	};
}

#endif
