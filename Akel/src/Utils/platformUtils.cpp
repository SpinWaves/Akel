// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/07/2021
// Updated : 23/02/2022

#include <Utils/utils.h>

namespace Ak
{
    void lockThreads(MutexHandel &lock)
    {
        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            EnterCriticalSection(lock);
        #else
            lock.lock();
        #endif
    }
    void unlockThreads(MutexHandel &lock)
    {
        #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            LeaveCriticalSection(lock);
        #else
            lock.unlock();
        #endif
    }
}
