// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/05/2021
// Updated : 27/01/2023

#ifndef __AK_ELTM_CONTEXT__
#define __AK_ELTM_CONTEXT__

#include <Akpch.h>
#include <Core/profile.h>
#include "token.h"
#include "ELTMerrors.h"

namespace Ak
{
	class AK_API ELTM
	{
		public:
			ELTM() = default;

			bool load(std::string path);
			
			inline bool reload(std::string path)
			{
				_texts.clear();
				_modules.clear();
				_files.clear();
				return load(std::move(path));
			}

			inline const std::string& getText(const std::string& ID, std::size_t line, const std::string& file, const std::string& function)
			{
				if(_is_error)
					return _error;
				if(_texts.count(ID))
					return _texts[ID];

				std::size_t found;

				if((found = ID.find('.')) != std::string::npos)
				{
					if(_modules.count(ID.substr(0, found)))
					{
						if(_modules[ID.substr(0, found)].count(ID.substr(found + 1)))
							return _modules[ID.substr(0, found)][ID.substr(found + 1)];
					}
					else
					{
						context_error(std::move(std::string("undefined module name : '" + ID.substr(0, found) + "'")), file, function, line).expose();
						return _error;
					}
				}

				context_error(std::move(std::string("undefined ID : '" + ID + "'")), file, function, line).expose();
				return _error;
			}

			inline std::unordered_map<std::string, std::string>& getTexts() { return _texts; }
			inline std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getModules() { return _modules; }

			~ELTM() = default;

		private:
			bool parse_token_value(class tk_iterator& it, const eltm_token& value);
			bool compile_id_declaration(class tk_iterator& it, std::string module_name = "");
			bool compile_module_declaration(class tk_iterator& it);

			std::unordered_map<std::string, std::string> _texts;
			std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _modules;

			std::vector<std::string> _files;

			std::filesystem::path _path;
			const std::string _error = "ELTM error";

			bool _is_error = false;
	};

	#undef getText
	#define getText(ID) getText(ID, __LINE__ - 1, __FILE__, AK_FUNC_SIG)
}

#endif // __AK_ELTM_CONTEXT__
