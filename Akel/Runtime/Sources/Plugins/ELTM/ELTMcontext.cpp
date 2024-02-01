// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/05/2021
// Updated : 01/02/2024

#include <Plugins/ELTM/ELTMcontext.h>
#include <Plugins/ELTM/TkIterator.h>
#include <Plugins/ELTM/File.h>

namespace Ak
{
	bool ELTM::ParseTokenValue(TkIterator& it, const EltmToken& value)
	{
		if(it->HasValue(value))
		{
			++it;
			return true;
		}
		ExpectedSyntaxError(std::to_string(value), m_path.string(), it->GetLine()).Expose();
		return false;
	}

	bool ELTM::CompileIdDeclaration(TkIterator& it, std::string module_name)
	{
		if(!ParseTokenValue(it, EltmToken::kw_let))
			return false;

		if(!it->IsIdentifier())
		{
			UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
			return false;
		}

		std::string id_name = it->GetIdentifier().name;

		if((!module_name.empty() && m_modules[module_name].count(id_name)) || (module_name.empty() && m_texts.count(id_name)))
		{
			AlreadyDeclaredError(std::move(id_name), m_path.string(), it->GetLine()).Expose();
			return false;
		}

		it++;

		if(!ParseTokenValue(it, EltmToken::assign))
			return false;

		if(!it->IsString() && !it->HasValue(EltmToken::kw_get))
		{
			UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
			return false;
		}

		std::string text;

		for(; it(); it++)
		{
			if(it->IsString())
				text.append(it->GetString());
			else if(it->HasValue(EltmToken::kw_get))
			{
				if(!ParseTokenValue(it, EltmToken::kw_get))
					return false;
				if(!ParseTokenValue(it, EltmToken::par_open))
					return false;
				if(!it->IsIdentifier())
				{
					UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
					return false;
				}
				if(m_texts.count(it->GetIdentifier().name))
					text.append(m_texts[it->GetIdentifier().name]);
				else if(!module_name.empty() && m_modules[module_name].count(it->GetIdentifier().name))
					text.append(m_modules[module_name][it->GetIdentifier().name]);
				else
				{
					UnknownIdError(it->GetIdentifier().name, m_path.string(), it->GetLine()).Expose();
					return false;
				}
				it++;
				if(!it->HasValue(EltmToken::par_close))
				{
					UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
					return false;
				}
			}
			else
				break;
		}

		if(module_name.empty())
			m_texts[std::move(id_name)] = std::move(text);
		else
			m_modules[std::move(module_name)][std::move(id_name)] = std::move(text);

		return true;
	}

	bool ELTM::CompileModuleDeclaration(TkIterator& it)
	{
		if(!ParseTokenValue(it, EltmToken::kw_begin))
			return false;
		if(!ParseTokenValue(it, EltmToken::kw_module))
			return false;

		if(!it->IsIdentifier())
		{
			UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
			return false;
		}

		std::string module_name = it->GetIdentifier().name;
		it++;

		while(it())
		{
			if(it->HasValue(EltmToken::kw_let))
			{
				if(!CompileIdDeclaration(it, module_name))
					return false;
			}
			else
			{
				UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
				return false;
			}
			if(it->HasValue(EltmToken::kw_end))
				break;

			if(!it->IsKeyword())
				it++;
		}

		if(!ParseTokenValue(it, EltmToken::kw_end))
			return false;
		if(!ParseTokenValue(it, EltmToken::kw_module))
			return false;

		return true;
	}

	bool ELTM::Load(const std::string& path)
	{
		File file(path.c_str());
		if(std::find(m_files.begin(), m_files.end(), path) != m_files.end())
			return true;
		m_files.push_back(path);
		m_path = path;
		func::function<int()> get = [&]() { return file(); };
		StreamStack stream(&get, path);
		TkIterator it(stream);

		while(it())
		{
			if(!it->IsKeyword() || it->HasValue(EltmToken::kw_get))
			{
				UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
				m_error_raised = true;
				return false;
			}
			if(it->HasValue(EltmToken::kw_let))
			{
				if(!CompileIdDeclaration(it))
				{
					m_error_raised = true;
					return false;
				}
			}
			if(it->HasValue(EltmToken::kw_begin))
			{
				if(!CompileModuleDeclaration(it))
				{
					m_error_raised = true;
					return false;
				}
			}
			if(it->HasValue(EltmToken::kw_import))
			{
				it++;
				if(!it->IsString())
				{
					UnexpectedError(std::to_string(it->GetValue()), m_path.string(), it->GetLine()).Expose();
					m_error_raised = true;
					return false;
				}
				if(!Load(m_path.parent_path().string() + "/" + it->GetString()))
					return false;
				m_path = path;
			}

			if(!it->IsKeyword())
				it++;
		}

		return true;
	}
}
