// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/07/2021
// Updated : 30/03/2022

#include <Utils/utils.h>

namespace Ak
{
    Mutex::Mutex()
    {
        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
              InitializeCriticalSection(&_mutex);
        #endif
    }

    void Mutex::lockThreads()
    {
        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            EnterCriticalSection(&_mutex);
        #else
            _mutex.lock();
        #endif
    }
    void Mutex::unlockThreads()
    {
        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            LeaveCriticalSection(&_mutex);
        #else
            _mutex.unlock();
        #endif
    }

    Mutex::~Mutex()
    {
        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            DeleteCriticalSection(&_mutex);
        #endif
    }
}
