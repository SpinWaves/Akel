// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/03/2024
// Updated : 08/04/2024

#ifndef __AK_CORE_VIRTUAL_PATH__
#define __AK_CORE_VIRTUAL_PATH__

#include <Core/PreCompiled.h>

namespace Ak
{
	class AK_CORE_API VirtualPath
	{
		public:
			VirtualPath() = default;
			VirtualPath(std::string_view path);

			std::string GetExtension() const;
			std::string GetFilename() const;
			std::string GetStem() const;

			VirtualPath GetParentPath() const;

			VirtualPath operator/(const VirtualPath& path);

			std::string ToString() const;

			inline bool IsEmpty() const noexcept { return m_path_steps.empty(); }
			inline void Clear() { m_path_steps.clear(); m_is_absolute = false; }
			inline std::size_t GetLength() const { return m_path_steps.size(); }
			inline bool IsAbsolute() const noexcept { return m_is_absolute; }

			friend std::ostream& operator<<(std::ostream& os, const VirtualPath& path);

			~VirtualPath() = default;

		private:
			std::vector<std::string> m_path_steps;
			bool m_is_absolute = false;
	};
}

#endif
