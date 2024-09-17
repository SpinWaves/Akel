// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_ELTM_FILE__
#define __AK_ELTM_FILE__

#include <Plugins/ELTM/PreCompiled.h>

namespace Ak
{
	class File
	{
		public:
			File(const char* path);
			File(const File&) = delete;

			File& operator=(const File&) = delete;
			inline int operator()() const { return std::fgetc(m_fp); }
			inline bool IsEof() const { return std::feof(m_fp); }
			inline const std::string& GetPath() const { return m_path; }

			~File();

		private:
			std::string m_path;
			FILE* m_fp;
	};
}

#endif // __AK_ELTM_FILE__

