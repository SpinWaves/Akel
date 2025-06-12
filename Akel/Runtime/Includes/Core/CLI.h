// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_CORE_CLI_H
#define AK_CORE_CLI_H

#include <Core/PreCompiled.h>
#include <Core/Singleton.h>

namespace Ak
{
	class AK_CORE_API CommandLineInterface : public Singleton<CommandLineInterface>
	{
		friend Singleton<CommandLineInterface>;

		public:
			inline std::optional<std::string> GetOption(std::string_view option) const;
			inline std::optional<std::string> GetArgument(std::string_view arg) const;
			inline bool HasFlag(std::string_view flag) const;
			inline const std::string& GetCommand() const;

			inline void Feed(int ac, char** av);

		private:
			CommandLineInterface() = default;
			~CommandLineInterface() = default;

		private:
			std::unordered_map<std::string, std::string> m_options;
			std::unordered_set<std::string> m_flags;
			std::unordered_set<std::string> m_args;
			std::string m_cmd;
	};
}

#include <Core/CLI.inl>

#endif
