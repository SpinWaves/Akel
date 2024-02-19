// This file is a part of Akel
// Authors : @kbz_8
// Created : 18/02/2024
// Updated : 18/02/2024

#pragma once
#include <Core/CLI.h>

namespace Ak
{
	std::optional<std::string> CommandLineInterface::GetOption(std::string_view option) const
	{
		auto it = m_options.find(static_cast<std::string>(option));
		if(it == m_options.end())
			return std::nullopt;
		return it->second;
	}

	std::optional<std::string> CommandLineInterface::GetArgument(std::string_view arg) const
	{
		auto it = std::find(m_args.begin(), m_args.end(), arg);
		if(it == m_args.end())
			return std::nullopt;
		return *it;
	}

	bool CommandLineInterface::HasFlag(std::string_view flag) const
	{
		return std::find(m_flags.begin(), m_flags.end(), flag) != m_flags.end();
	}

	const std::string& CommandLineInterface::GetCommand() const
	{
		return m_cmd;
	}

	void CommandLineInterface::Feed(int ac, char** av)
	{
		m_cmd = av[0];
		for(int i = 1; i < ac; i++)
		{
			std::string_view arg{ av[i] };
			if(arg.front() == '-')
			{
				arg.remove_prefix(1);
				if(arg.front() == '-') // in case of arg begenning with --
					arg.remove_prefix(1);
				std::size_t finder = arg.find_first_of('=');
				if(finder != std::string_view::npos)
					m_options.emplace(std::make_pair(arg.substr(0, finder - 1), arg.substr(finder)));
				else
					m_flags.emplace(arg);
			}
			else
				m_args.emplace(arg);
		}
	}
}
