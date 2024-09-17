// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

namespace Ak
{
	inline bool ELTM::Reload(const std::string& path)
	{
		m_texts.clear();
		m_modules.clear();
		m_files.clear();
		return Load(path);
	}

	inline const std::string& ELTM::GetText(const std::string& ID, std::size_t line, const std::string& file, const std::string& function)
	{
		if(m_error_raised)
			return c_error;
		if(m_texts.count(ID))
			return m_texts[ID];

		std::size_t found;

		if((found = ID.find('.')) != std::string::npos)
		{
			if(m_modules.count(ID.substr(0, found)))
			{
				if(m_modules[ID.substr(0, found)].count(ID.substr(found + 1)))
					return m_modules[ID.substr(0, found)][ID.substr(found + 1)];
			}
			else
			{
				ContextError("undefined module name : '" + ID.substr(0, found) + "'", file, function, line).Expose();
				return c_error;
			}
		}

		ContextError("undefined ID : '" + ID + "'", file, function, line).Expose();
		return c_error;
	}
}
