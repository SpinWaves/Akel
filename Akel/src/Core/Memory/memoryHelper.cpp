// This file is a part of the Akel editor
// CREATED : 23/07/2021
// UPDATED : 24/07/2021

#include <Utils/utils.h>
#include <Core/core.h>

namespace Ak
{
    void InitMemoryHelper()
    {
    #ifndef AK_USE_JAM_MEMORY_HELPER
        __jam.init(4096 * 4096);
        __fixed1.init(16, 100);
        __fixed2.init(32, 200);
        __fixed3.init(96, 400);

        __jam.autoResize(true);
        __fixed1.autoResize(true);
        __fixed2.autoResize(true);
        __fixed3.autoResize(true);
    #else
        __jam.init(4096 * 4096);
        __jam.autoResize(true);
    #endif
    }
    void EndMemoryHelper()
    {
    #ifndef AK_USE_JAM_MEMORY_HELPER
        __jam.destroy();
        __fixed1.destroy();
        __fixed2.destroy();
        __fixed3.destroy();
    #else
        __jam.destroy();
    #endif
    }
}
