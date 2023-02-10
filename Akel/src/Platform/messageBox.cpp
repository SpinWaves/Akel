// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 10/02/2023

#include <Platform/platform.h>

namespace Ak
{
    void messageBox(enum LogType type, std::string message, std::string logReport, bool report)
    {
        const char* title;
		
		if(report)
			Core::log::report(type, logReport);

		if(pfd::settings::available())
		{
			pfd::icon icon;

			switch(type)
			{
				case MESSAGE:		icon = pfd::icon::info; title = "Akel Message"; break;
				case WARNING:
				case STRONG_WARNING:icon = pfd::icon::warning; title = "Akel Warning"; break;
				case ERROR:			icon = pfd::icon::error; title = "Akel Error"; break;
				case FATAL_ERROR:	icon = pfd::icon::error; title = "Akel Fatal Error"; break;
			}

			message.append("\n\nDo you want more informations ?");
			auto button = pfd::message(title, std::move(message), pfd::choice::yes_no, icon);

			if(button.result() == pfd::button::yes)
				pfd::message(title, std::move(logReport), pfd::choice::ok, icon);
			return;
		}

        int buttonid;
        uint32_t flag = SDL_MESSAGEBOX_INFORMATION;

		switch(type)
		{
			case MESSAGE:		flag = SDL_MESSAGEBOX_INFORMATION; title = "Akel Message"; break;
			case WARNING:
			case STRONG_WARNING:flag = SDL_MESSAGEBOX_WARNING; title = "Akel Warning"; break;
			case ERROR:			flag = SDL_MESSAGEBOX_ERROR; title = "Akel Error"; break;
			case FATAL_ERROR:	flag = SDL_MESSAGEBOX_ERROR; title = "Akel Fatal Error"; break;
		}
        
		SDL_MessageBoxButtonData buttons[] = {{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Ok"}, {0, 0, "More details"}};
        const SDL_MessageBoxColorScheme colorScheme = {{
                {56, 54, 53},
                {233, 233, 233},
                {180, 180, 180},
                {105, 102, 99},
                {160, 160, 160}
        }};
        SDL_MessageBoxData messageboxdata = { flag, nullptr, title, message.c_str(), SDL_arraysize(buttons), buttons, &colorScheme };
        SDL_ShowMessageBox(&messageboxdata, &buttonid);

        if(buttonid == 1)
			return;
		message.append(":\n");
		message.append(std::move(logReport));

		messageboxdata = { flag, nullptr, title, message.c_str(), SDL_arraysize(buttons) - 1, buttons, &colorScheme };
		SDL_ShowMessageBox(&messageboxdata, &buttonid);
    }
}
