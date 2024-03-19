// This file is a part of Akel
// Authors : @kbz_8
// Created : 18/03/2024
// Updated : 19/03/2024

#ifndef __AK_CORE_FILE__
#define __AK_CORE_FILE__

#include <Core/PreCompiled.h>
#include <Core/Enums.h>

namespace Ak
{
	class AK_CORE_API File
	{
		public:
			File() = default;
			File(const std::filesystem::path& filepath, std::uint32_t flags);

			bool Open(const std::filesystem::path& filepath, std::uint32_t flags);
			void Close();

			template <typename T>
			inline void operator<<(T&& t) { m_stream << std::forward<T>(t); }

			inline bool IsOpen() const { return m_stream.is_open(); }
			inline bool Exists() const { return std::filesystem::exists(m_filepath); }

			inline std::size_t GetSize() const { return  std::filesystem::file_size(m_filepath); }
			inline std::filesystem::path GetPath() const { return m_filepath; }
			inline std::filesystem::path GetDirectory() const { return m_filepath.parent_path(); }

			~File() = default;

		private:
			std::filesystem::path m_filepath;
			std::fstream m_stream;
	};
}

#endif
