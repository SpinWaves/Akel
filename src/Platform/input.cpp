// This file is a part of AtlasEngine
// CREATED : 04/04/2021
// UPDATED : 04/05/2021

#include <Platform/platform.h>

namespace AE
{
    Input::Input()
    {
        _x = 0;
        _y = 0;
        _xRel = 0;
        _yRel = 0;

        for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        {
            _touches[0][i] = false;
            _touches[1][i] = false;
            if(i < 8)
			{
                _boutonsSouris[0][i] = false;
                _boutonsSouris[1][i] = false;
			}
        }
    }

    void Input::update()
    {
        _xRel = 0;
        _yRel = 0;

        for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        {
            _touches[0][i] = false;
            if(i < 8)
                _boutonsSouris[0][i] = false;
        }

        while(SDL_PollEvent(&evenements))
        {
            if(evenements.window.event == SDL_WINDOWEVENT_CLOSE) 
                _end = true;

            switch(evenements.type) 
            {
                case SDL_KEYDOWN: 
                    _touches[1][evenements.key.keysym.scancode] = true;
                    _touches[0][evenements.key.keysym.scancode] = false;
                break;


                case SDL_KEYUP: 
                    _touches[1][evenements.key.keysym.scancode] = false;
                    _touches[0][evenements.key.keysym.scancode] = true;
                break;

                case SDL_MOUSEBUTTONDOWN: 
                    _boutonsSouris[1][evenements.button.button] = true;
                    _boutonsSouris[0][evenements.button.button] = false;
                break;

                case SDL_MOUSEBUTTONUP: 
                    _boutonsSouris[1][evenements.button.button] = false;
                    _boutonsSouris[0][evenements.button.button] = true;
                break;

                case SDL_TEXTINPUT: 
                    if(_isTextInputAllow)
                    {
                        _text_input_string = evenements.text.text;
                        _isTyping = true;
                    }
                break;

                default: break;
            }

            if(evenements.type == SDL_MOUSEMOTION) 
            {
                    _x = evenements.motion.x;
                    _y = evenements.motion.y;

                    _xRel = evenements.motion.xrel;
                    _yRel = evenements.motion.yrel;
            }
        }
    }

    void Input::activateTextInput(bool activate)
    {
        _isTextInputAllow = activate;
    }

    bool Input::getInKey(const SDL_Scancode touche, enum ButtonACTION type) const
    {
        if(type == DOWN)
            return _touches[1][touche];
        return _touches[0][touche];
    }

    bool Input::getInMouse(const Uint8 bouton, enum ButtonACTION type) const
    {
        if(type == DOWN) 
            return _boutonsSouris[1][bouton];
        return _boutonsSouris[0][bouton]; 
    }

    bool Input::getMovMouse() const
    {
        if(!_xRel && !_yRel) 
            return false;
        return true;
    }

    int Input::getX() const
    {
        return _x; 
    }
    int Input::getY() const
    {
        return _y; 
    }

    int Input::getXRel() const
    {
        return _xRel;
    }
    int Input::getYRel() const
    {
        return _yRel;
    }

    std::string Input::getTextEntry()
    {
        return _text_input_string;
    }

    bool Input::isEnded() const
    {
        return _end;
    }

    void Input::finish()
    {
        _end = true;
    }
}
