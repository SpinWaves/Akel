// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/07/2021
// Updated : 30/03/2022

#ifndef __AK_PLATFORM_UTILS__
#define __AK_PLATFORM_UTILS__

#include <Akpch.h>
#include "nonCopyable.h"
#include <Core/profile.h>

namespace Ak
{
    class Mutex : public non_copyable
    {
        public:
            Mutex();

            void lockThreads();
            void unlockThreads();

            ~Mutex();
        
        private:
            /**
             * Critical sections perform better in pre-2015 Visual Studio,
             * so it's best to use them. However, since Visual Studio 2015,
             * std::mutex are much more efficient than critical sections.
             */
            #if defined(AK_PLATFORM_WINDOWS) && defined(_MSC_VER) && _MSC_VER < 1900
                CRITICAL_SECTION _mutex;
            #else
                std::mutex _mutex;
            #endif
    };
}

#endif // __AK_PLATFORM_UTILS__
