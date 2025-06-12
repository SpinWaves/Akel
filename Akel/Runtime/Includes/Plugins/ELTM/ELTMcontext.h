// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_ELTM_CONTEXT_H
#define AK_ELTM_CONTEXT_H

#include <Plugins/ELTM/PreCompiled.h>
#include <Plugins/ELTM/Token.h>
#include <Plugins/ELTM/Errors.h>

namespace Ak
{
	class AK_ELTM_API ELTM
	{
		public:
			ELTM() = default;

			bool Load(const std::string& path);
			inline bool Reload(const std::string& path);
			inline const std::string& GetText(const std::string& ID, std::size_t line, const std::string& file, const std::string& function);

			~ELTM() = default;

		private:
			bool ParseTokenValue(class TkIterator& it, const EltmToken& value);
			bool CompileIdDeclaration(class TkIterator& it, std::string module_name = "");
			bool CompileModuleDeclaration(class TkIterator& it);

		private:
			std::unordered_map<std::string, std::string> m_texts;
			std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_modules;

			std::vector<std::string> m_files;

			std::filesystem::path m_path;

			const std::string c_error = "ELTM error";

			bool m_error_raised = false;
	};
}

#include <Plugins/ELTM/ELTMcontext.inl>

namespace Ak
{
	#undef GetText
	#define GetText(ID) GetText(ID, __LINE__ - 1, __FILE__, AK_FUNC_SIG)
}

#endif // AK_ELTM_CONTEXT_H
