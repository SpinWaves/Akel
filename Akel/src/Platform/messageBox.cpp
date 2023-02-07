// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 22/01/2023

#include <Platform/platform.h>

namespace Ak
{
    void messageBox(enum LogType type, std::string message, std::string logReport)
    {
        SDL_MessageBoxButtonData buttons[] = {{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Ok"}, {0, 0, "More details"}};

        const SDL_MessageBoxColorScheme colorScheme = {{
                {56, 54, 53},
                {233, 233, 233},
                {180, 180, 180},
                {105, 102, 99},
                {160, 160, 160}
        }};

        uint32_t flag = SDL_MESSAGEBOX_INFORMATION;
        const char* title;

        switch(type)
        {
            case MESSAGE:		flag = SDL_MESSAGEBOX_INFORMATION; title = "Akel Message"; break;
            case WARNING:		flag = SDL_MESSAGEBOX_WARNING; title = "Akel Warning"; break;
			case ERROR:			flag = SDL_MESSAGEBOX_ERROR; title = "Akel Error"; break;
            case FATAL_ERROR:	flag = SDL_MESSAGEBOX_ERROR; title = "Akel Fatal Error"; break;

            default: break;
        }

        SDL_MessageBoxData messageboxdata = { flag, nullptr, title, message.c_str(), SDL_arraysize(buttons), buttons, &colorScheme };

        int buttonid;

        SDL_ShowMessageBox(&messageboxdata, &buttonid);

        if(buttonid == 1)
		{
            Core::log::report(type, logReport);
			return;
		}
		message.append(":\n");
		message.append(logReport);

		messageboxdata = { flag, nullptr, title, message.c_str(), SDL_arraysize(buttons) - 1, buttons, &colorScheme };

		SDL_ShowMessageBox(&messageboxdata, &buttonid);
		Core::log::report(type, std::move(logReport));
    }
}
