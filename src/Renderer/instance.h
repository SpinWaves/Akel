// This file is a part of AtlasEngine
// CREATED : 10/04/2021
// UPDATED : 03/06/2021

#ifndef __AE_INSTANCE__
#define __AE_INSTANCE__

#include <AEpch.h>

namespace AE
{
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    #ifdef AE_DEBUG
        constexpr bool enableValidationLayers = true;
    #else
        constexpr bool enableValidationLayers = false;
    #endif

    class Instance
    {
        public:
            void init(SDL_Window* window);
            void destroy();
            virtual ~Instance();
        
        private:
            bool checkValidationLayerSupport();
            VkInstance instance;
    };
}

#endif // __AE_INSTANCE__
