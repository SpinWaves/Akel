// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 15/05/2022

#include <Modules/Kila/file.h>
#include <Modules/Kila/errors.h>

namespace Ak::Kl
{
    File::File(const char* path)
    {
        _fp = fopen(path, "rt");
        if(!_fp)
            file_not_found(path).expose();
        _path = path;
    }
    
    File::~File()
    {
        if(_fp != nullptr)
            fclose(_fp);
    }    
}
