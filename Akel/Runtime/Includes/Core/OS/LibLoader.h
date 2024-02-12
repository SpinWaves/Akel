// This file is a part of Akel
// Authors : @maldavid
// Created : 12/02/2024
// Updated : 12/02/2024

#ifndef __AK_CORE_OS_LIB_LOADER__
#define __AK_CORE_OS_LIB_LOADER__

#include <Core/PreCompiled.h>
#include <Utils/NonCopyable.h>

namespace Ak
{
	using LibFunc = void (*)(void);

	class AK_CORE_API LibLoader : public NonCopyable
	{
		public:
			LibLoader() = default;

			virtual LibFunc GetSymbol(const char* symbol) const = 0;
			inline const std::filesystem::path& GetCurrentlyLoadedLib() const { return m_currently_loaded; }

			virtual bool Load(const std::filesystem::path& path) = 0;
			virtual void UnloadCurrentLib() = 0;

			~LibLoader() = default;

		private:
			std::filesystem::path m_currently_loaded;
	};
}

#endif
