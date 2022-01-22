// This file is a part of Akel
// CREATED : 03/04/2021
// UPDATED : 22/01/2022

#include <Platform/platform.h>

namespace Ak
{
    void messageBox(enum LogType type, std::string message, std::string logReport)
    {
        SDL_MessageBoxButtonData buttons[] = {{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Ok"}, {0, 0, "More details"}};

        const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                {56, 54, 53},
                /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                {233, 233, 233},
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                {180, 180, 180},
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                {105, 102, 99},
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                {160, 160, 160}
            }
        };

        Uint32 flag = SDL_MESSAGEBOX_INFORMATION;
        const char* title;

        switch(type)
        {
            case MESSAGE: flag = SDL_MESSAGEBOX_INFORMATION; title = "Message"; break;
            case WARNING: flag = SDL_MESSAGEBOX_WARNING; title = "Warning"; break;
            case ERROR:   flag = SDL_MESSAGEBOX_ERROR; title = "Error"; break;
            case FATAL_ERROR:   flag = SDL_MESSAGEBOX_ERROR; title = "Fatal Error"; break;

            default: break;
        }

        SDL_MessageBoxData messageboxdata = {
            flag, 
            NULL, 
            title, 
            message.c_str(),
            SDL_arraysize(buttons),
            buttons,
            &colorScheme
        };

        int buttonid;

        SDL_ShowMessageBox(&messageboxdata, &buttonid);

        if(buttonid == 1)
		{
            Core::log::report(type, logReport);
			return;
		}
		message.append(":\n");
		message.append(logReport);

		 messageboxdata = {
			flag, /* .flags */
			NULL, /* .window */
			title, /* .title */
			message.c_str(), /* .message */
			SDL_arraysize(buttons) - 1, /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
		};

		SDL_ShowMessageBox(&messageboxdata, &buttonid);
		if(buttonid == 1)
			Core::log::report(type, logReport);
    }
}
