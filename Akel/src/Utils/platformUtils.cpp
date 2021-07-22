// This file is a part of Akel
// CREATED : 22/07/2021
// UPDATED : 22/07/2021

#include <Utils/utils.h>

namespace Ak
{
    void lockThreads(MutexHandel &lock)
    {
        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            EnterCriticalSection(lock);
        #else
            lock.lock();
        #endif
    }
    void unlockThreads(MutexHandel &lock)
    {
        #if defined(Ak_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
            LeaveCriticalSection(lock);
        #else
            lock.unlock();
        #endif
    }
}
