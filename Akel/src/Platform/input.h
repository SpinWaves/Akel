// This file is a part of Akel
// CREATED : 04/04/2021
// UPDATED : 04/07/2021

#ifndef __AK_INPUT__
#define __AK_INPUT__

#include <Akpch.h>
#include <Platform/inputScanCode.h>

enum ButtonACTION
{
    UP,
    DOWN
};

namespace Ak
{
    class Input
    {
        public:
            Input();

            void update();

            bool getInKey(const SDL_Scancode touche, enum ButtonACTION type = UP) const;

            bool getInMouse(const Uint8 bouton, enum ButtonACTION type = UP) const;
            bool getMovMouse() const;

            int getX() const;
            int getY() const;

            int getXRel() const;
            int getYRel() const;

            void activateTextInput(bool activate);

            std::string getTextEntry();
            bool _isTyping = false;

            bool isEnded() const;
            void finish();

			SDL_Event* getNativeEvent()
			{
				return &evenements;
			}


        private:
            SDL_Event evenements;
            std::array<std::array<bool, 2>, AK_NUM_SCANCODES> _touches; // 0 = UP, 1 = DOWN
            std::array<std::array<bool, 2>, 8> _boutonsSouris;		   // 0 = UP, 1 = DOWN

            std::string _text_input_string = " ";

            int _x;
            int _y; 
            int _xRel; 
            int _yRel; 

            bool _end = false;

            bool _isTextInputAllow = false;
    };
}

#endif // __AK_INPUT__
