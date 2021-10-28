// This file is a part of the Akel editor
// CREATED : 28/10/2021
// UPDATED : 28/10/2021

#ifndef __AK_EDITOR_ELTM_EDITOR__
#define __AK_EDITOR_ELTM_EDITOR__

#include <AkEpch.h>

class ELTM_editor
{
    public:
        explicit ELTM_editor(const std::string& name);
        void render(int width, int height);
        void load(const std::string& filename);
        ~ELTM_editor() = default;
    
    private:
        std::string _file;
        std::string _name;
		Ak::unique_ptr_w<Ak::ELTM> _eltm;
        int _height, _width;

        void editor();
};

#endif // __AK_EDITOR_ELTM_EDITOR__
