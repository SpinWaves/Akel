// This file is a part of the Akel editor
// CREATED : 10/07/2021
// UPDATED : 10/07/2021

#ifndef __AK_SHELL__
#define __AK_SHELL__

#include <Panels/shell/parser.h>

class Shell : private Parser
{
	public:
		explicit Shell();
		void command(std::string command);

	private:
};

#endif // __AK_SHELL__

