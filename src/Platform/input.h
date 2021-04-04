// This file is a part of AtlasEngine
// CREATED : 04/04/2021
// UPDATED : 04/04/2021

#ifndef __INPUT__
#define __INPUT__

#include <AEpch.h>
#include <Platform/inputScanCode.h>

enum ButtonACTION
{
    UP,
    DOWN
};

namespace AE
{
    class Input
    {
        public:
            Input();

            void update();

            bool getInKey(const SDL_Scancode touche, enum ButtonACTION type = DOWN) const;

            bool getInMouse(const Uint8 bouton, enum ButtonACTION type = DOWN) const;
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


        private:
            SDL_Event evenements;
            bool _touchesDOWN[SDL_NUM_SCANCODES];
            bool _boutonsSourisDOWN[8];
            bool _touchesUP[SDL_NUM_SCANCODES];
            bool _boutonsSourisUP[8];

            std::string _text_input_string = " ";

            int _x;
            int _y; 
            int _xRel; 
            int _yRel; 

            bool _end = false;

            bool _isTextInputAllow = false;
    };
}

#endif // __INPUT__
