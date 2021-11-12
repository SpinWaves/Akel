// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 12/11/2021

#include <Modules/Kila/file.h>
#include <Modules/Kila/errors.h>

namespace Ak::Kl
{
    File::File(const char* path)
    {
        _fp = fopen(path, "rt");
        if(!_fp)
            file_not_found(path).expose();
    }
    
    File::~File()
    {
        if(_fp)
            fclose(_fp);
    }    
}
