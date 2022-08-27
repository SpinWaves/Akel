// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/08/2022
// Updated : 27/08/2022

#ifndef __AK_ELTM_FILE__
#define __AK_ELTM_FILE__

#include <Akpch.h>

namespace Ak
{
	class File
	{
		public:
			File(const char* path);
			File(const File&) = delete;

			void operator=(const File&) = delete;
			inline int operator()() const { return std::fgetc(_fp); }
			inline bool is_eof() const { return std::feof(_fp); }
			inline const std::string& get_path() const { return _path; }

			~File();

		private:
			std::string _path;
			FILE* _fp;
	};
}

#endif // __AK_ELTM_FILE__

