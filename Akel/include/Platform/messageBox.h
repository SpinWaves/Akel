// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2021
// Updated : 07/06/2023

#ifndef __AK_MESSAGEBOX__
#define __AK_MESSAGEBOX__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
    void messageBox(LogType type, std::string message, std::string logReport, bool report = true);
}

#endif // __AK_MESSAGEBOX__
