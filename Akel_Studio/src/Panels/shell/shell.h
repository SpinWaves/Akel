// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/07/2021
// Updated : 12/09/2022

#ifndef __AK_SHELL__
#define __AK_SHELL__

#include <Panels/shell/parser.h>

class Shell : private Parser
{
	public:
		Shell(std::shared_ptr<Ak::ELTM> eltm);
		void command(std::string command);
		
		inline void print(std::string print, uint8_t type = 0)
		{
			_out.emplace_back(type, std::move(print), Ak::Time::getCurrentTime());
		}

		inline std::vector<std::tuple<uint8_t, std::string, __time>> getOutPut() { return _out; }

		inline bool quit() const noexcept { return _quit; }

		bool ee = false;

	private:
		std::string exec(std::string command);

		std::vector<std::tuple<uint8_t, std::string, __time>> _out;
		std::vector<std::tuple<uint8_t, std::string, __time>> _history;
		std::shared_ptr<Ak::ELTM> _eltm;
		bool _quit = false;
};

#endif // __AK_SHELL__
