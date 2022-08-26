// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/05/2021
// Updated : 26/08/2022

#ifndef __AK_ELTM_CONTEXT__
#define __AK_ELTM_CONTEXT__

#include <Akpch.h>
#include <Modules/ELTM/ELTMerrors.h>
#include <Utils/utils.h>
#include <Core/profile.h>

namespace Ak
{
	class ELTM
	{
		public:
			ELTM(bool is_global = true);
			bool load(std::string file);
			inline bool reload(std::string file)
			{
				_texts.clear();
				_current_texts.clear();
				_modules.clear();
				_current_modules.clear();
				return load(std::move(file));
			}

			inline static std::string getText(const std::string& ID, std::size_t line, const std::string& file, const std::string& function)
			{
				if(_isError)
					return "error";
				if(_texts.count(ID))
					return _texts[ID];

				std::string moduleName;
				std::string moduleID;
				std::size_t found;

				if((found = ID.find('.')) != std::string::npos)
				{
					moduleName.append(ID, 0, found);
					if(_modules.count(moduleName))
					{
						moduleID.append(ID, found + 1, ID.length());
						if(_modules[moduleName].count(moduleID))
							return _modules[moduleName][moduleID];
					}
					context_error(std::move(std::string("undefined module name : " + moduleName)), file, function, line).expose();
					return "error";
				}

				context_error(std::move(std::string("undefined ID : " + ID)), file, function, line).expose();
				return "error";
			}

			std::string getLocalText(const std::string& ID, size_t line, const std::string& file, const std::string& function)
			{
				if(_isError)
					return "error";

				if(_current_texts.count(ID))
					return _current_texts[ID];

				size_t found = 0;

				if((found = ID.find(".")) != std::string::npos)
				{
					std::string moduleName = "";
					std::string moduleID = "";
					moduleName.append(ID, 0, found);
					if(_current_modules.count(moduleName))
					{
						moduleID.append(ID, found + 1, ID.length());
						if(_current_modules[moduleName].count(moduleID))
							return _current_modules[moduleName][moduleID];
					}
					else
					{
						ELTMerrors error = context_error(std::string("undefined module name : " + moduleName), file, function, line);
						std::cout << red << error.what() << def << std::endl;
						return "error";
					}
				}

				ELTMerrors error = context_error(std::string("undefined ID : " + ID), file, function, line);
				std::cout << red << error.what() << def << std::endl;
				return "error";
			}

			const std::string& getFile() const noexcept { return _file; }

			inline std::unordered_map<std::string, std::string>& getCurrentTexts() { return _current_texts; }
			inline std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getCurrentModules() { return _current_modules; }

			~ELTM() = default;

		private:
			bool setID(bool isNewID);

			static inline std::unordered_map<std::string, std::string> _texts;
			std::unordered_map<std::string, std::string> _current_texts;
			static inline std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _modules;
			std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _current_modules;
			
			std::vector<ELTM> _imports;

			StreamStack _stream;
			std::string _file;
			std::size_t _line = 0;

			static inline bool _isError = false;
			bool _is_global = true;
	};

	#undef getText
	#define getText(ID) getText(ID, __LINE__, __FILE__, AK_FUNC_SIG)
	#undef getLocalText
	#define getLocalText(ID) getLocalText(ID, __LINE__, __FILE__, AK_FUNC_SIG)
}

#endif // __AK_ELTM_CONTEXT__
