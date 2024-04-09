// This file is a part of Akel
// Authors : @kbz_8
// Created : 21/03/2024
// Updated : 21/03/2024

#include <Core/VirtualPath.h>

namespace Ak
{
	VirtualPath::VirtualPath(std::string_view path)
	{
		using namespace std::literals;
		m_is_absolute = (path.substr(0, 2) == ":/"sv);

		std::size_t last_pos = 0;
		std::size_t pos = path.find_first_of("/", last_pos);
		while(last_pos != std::string_view::npos)
		{
			if(pos != last_pos)
				m_path_steps.emplace_back(path.substr(pos, pos - last_pos));
			last_pos = pos;
			if(last_pos == std::string_view::npos || last_pos + 1 == path.length())
				break;
			pos = path.find_first_of("/", last_pos++);
		}
	}

	std::string VirtualPath::GetExtension() const
	{
		const std::string& name = GetFilename();
		std::size_t pos = name.find_last_of(".");
		if(pos == std::string::npos)
			return "";
		return name.substr(pos + 1);
	}

	std::string VirtualPath::GetFilename() const
	{
		if(IsEmpty())
			return "";
		const std::string& last = m_path_steps.back();
		return last;
	}

	std::string VirtualPath::GetStem() const
	{
		const std::string& name = GetFilename();
		std::size_t pos = name.find_last_of(".");
		if(pos == std::string::npos)
			return name;
		return name.substr(0, pos);
	}

	VirtualPath VirtualPath::GetParentPath() const
	{
		VirtualPath result;
		result.m_is_absolute = m_is_absolute;

		if(m_path_steps.empty())
		{
			if(!m_is_absolute)
				result.m_path_steps.push_back("..");
		}
		else
		{
			std::size_t until = m_path_steps.size() - 1;
			for(std::size_t i = 0; i < until; i++)
				result.m_path_steps.push_back(m_path_steps[i]);
		}
		return result;
	}

	VirtualPath VirtualPath::operator/(const VirtualPath& rhs)
	{
		if(rhs.m_is_absolute)
			FatalError("Virtual Path : expected a relative path");
		VirtualPath result(*this);
		for(std::size_t i = 0; i < rhs.m_path_steps.size(); i++)
			result.m_path_steps.push_back(rhs.m_path_steps[i]);
		return result;
	}

	std::string VirtualPath::ToString() const
	{
		std::ostringstream oss;
		if(m_is_absolute)
			oss << ":/";
		for(std::size_t i = 0; i < m_path_steps.size(); i++)
		{
			oss << m_path_steps[i];
			if(i + 1 < m_path_steps.size())
				oss << '/';
		}
		return oss.str();
	}

	std::ostream& operator<<(std::ostream& os, const VirtualPath& path)
	{
		os << path.ToString();
		return os;
	}
}
