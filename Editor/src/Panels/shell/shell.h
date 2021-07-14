// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 13/07/2021

#ifndef __AK_SHELL__
#define __AK_SHELL__

#include <Panels/shell/parser.h>

class Shell : private Parser
{
	public:
		explicit Shell();
		void command(std::string command);
		void print(std::string print, uint8_t type = 0);
		bool quit();
		std::vector<std::tuple<uint8_t, std::string, __time>> getOutPut();

	private:
		std::vector<std::tuple<uint8_t, std::string, __time>> _out;
		bool _quit = false;
};

#endif // __AK_SHELL__

