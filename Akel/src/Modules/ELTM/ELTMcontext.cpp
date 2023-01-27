// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/05/2021
// Updated : 27/01/2023

#include <Modules/ELTM/eltm.h>

namespace Ak
{
	bool ELTM::parse_token_value(tk_iterator& it, const eltm_token& value)
	{
		if(it->has_value(value))
		{
			++it;
			return true;
		}
		expected_syntax_error(std::to_string(value).c_str(), _path, it->get_line()).expose();
		return false;
	}

	bool ELTM::compile_id_declaration(tk_iterator& it, std::string module_name)
	{
		if(!parse_token_value(it, eltm_token::kw_let))
			return false;

		if(!it->is_identifier())
		{
			unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
			return false;
		}

		std::string id_name = it->get_identifier().name;

		if((!module_name.empty() && _modules[module_name].count(id_name)) || (module_name.empty() && _texts.count(id_name)))
		{
			already_declared_error(std::move(id_name), _path, it->get_line()).expose();
			return false;
		}

		it++;

		if(!parse_token_value(it, eltm_token::assign))
			return false;

		if(!it->is_string() && !it->has_value(eltm_token::kw_get))
		{
			unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
			return false;
		}

		std::string text;

		for(; it(); it++)
		{
			if(it->is_string())
				text.append(it->get_string());
			else if(it->has_value(eltm_token::kw_get))
			{
				if(!parse_token_value(it, eltm_token::kw_get))
					return false;
				if(!parse_token_value(it, eltm_token::par_open))
					return false;
				if(!it->is_identifier())
				{
					unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
					return false;
				}
				if(_texts.count(it->get_identifier().name))
					text.append(_texts[it->get_identifier().name]);
				else if(!module_name.empty() && _modules[module_name].count(it->get_identifier().name))
					text.append(_modules[module_name][it->get_identifier().name]);
				else
				{
					unknown_id_error(it->get_identifier().name, _path, it->get_line()).expose();
					return false;
				}
				it++;
				if(!it->has_value(eltm_token::par_close))
				{
					unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
					return false;
				}
			}
			else
				break;
		}

		if(module_name.empty())
			_texts[std::move(id_name)] = std::move(text);
		else
			_modules[std::move(module_name)][std::move(id_name)] = std::move(text);

		return true;
	}

	bool ELTM::compile_module_declaration(tk_iterator& it)
	{
		if(!parse_token_value(it, eltm_token::kw_begin))
			return false;
		if(!parse_token_value(it, eltm_token::kw_module))
			return false;

		if(!it->is_identifier())
		{
			unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
			return false;
		}

		std::string module_name = it->get_identifier().name;
		it++;

		while(it())
		{
			if(it->has_value(eltm_token::kw_let))
			{
				if(!compile_id_declaration(it, module_name))
					return false;
			}
			else
			{
				unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
				return false;
			}
			if(it->has_value(eltm_token::kw_end))
				break;

			if(!it->is_keyword())
				it++;
		}

		if(!parse_token_value(it, eltm_token::kw_end))
			return false;
		if(!parse_token_value(it, eltm_token::kw_module))
			return false;

		return true;
	}

	bool ELTM::load(std::string path)
	{
		File file(path.c_str());
		if(std::find(_files.begin(), _files.end(), path) != _files.end())
			return true;
		_files.push_back(path);
		_path = path;
		func::function<int()> get = [&]() { return file(); };
		StreamStack stream(&get, path);
		tk_iterator it(stream);

		while(it())
		{
			if(!it->is_keyword() || it->has_value(eltm_token::kw_get))
			{
				unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
				_is_error = true;
				return false;
			}
			if(it->has_value(eltm_token::kw_let))
			{
				if(!compile_id_declaration(it))
				{
					_is_error = true;
					return false;
				}
			}
			if(it->has_value(eltm_token::kw_begin))
			{
				if(!compile_module_declaration(it))
				{
					_is_error = true;
					return false;
				}
			}
			if(it->has_value(eltm_token::kw_import))
			{
				it++;
				if(!it->is_string())
				{
					unexpected_error(std::move(std::to_string(it->get_value())), _path, it->get_line()).expose();
					_is_error = true;
					return false;
				}
				if(!load(_path.parent_path().string() + "/" + it->get_string()))
					return false;
				_path = path;
			}

			if(!it->is_keyword())
				it++;
		}

		return true;
	}
}
