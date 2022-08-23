// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 21/08/2022

#ifndef __AK_PLAIN_APPLICATION__
#define __AK_PLAIN_APPLICATION__

#include <Core/core.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
    class PlainApplication : public Application
    {
        public:
			PlainApplication(const char* name = "Akel Window");

            ~PlainApplication() = default;

        protected:
            WindowComponent* window = nullptr;
            RendererComponent* renderer = nullptr;
    };
}

#endif // __AK_PLAIN_APPLICATION__
