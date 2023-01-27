// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/04/2021
// Updated : 30/08/2022

#ifndef __AK_HARDWARE_INFO__
#define __AK_HARDWARE_INFO__

#include <Akpch.h>

namespace Ak::Core
{
    void printCPUinfo();
    void printGPUinfo();

	const class CPU& getCpuInfo();
}

#endif // __AK_HARDWARE_INFO__
