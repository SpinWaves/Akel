// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/08/2021
// Updated : 28/03/2023

#ifndef __AK_OPENAL__
#define __AK_OPENAL__

#include <Akpch.h>
#include <Core/profile.h>

namespace Ak
{
    class OpenAL
    {
        public:
            OpenAL();

            bool initOAL();
            void shutdownOAL();

            ~OpenAL();

        private:
			struct _Pimpl;
			_Pimpl* _impl = nullptr;
    };
}

#endif // __AK_OPENAL__
