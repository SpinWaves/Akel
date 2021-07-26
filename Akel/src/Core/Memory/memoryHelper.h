// This file is a part of the Akel editor
// CREATED : 23/07/2021
// UPDATED : 25/07/2021

#ifndef __AK_MEMORY_HELPER__
#define __AK_MEMORY_HELPER__

#include <Akpch.h>

namespace Ak
{
    static JamAllocator __jam;
    static FixedAllocator __fixed1;
    static FixedAllocator __fixed2;
    static FixedAllocator __fixed3;

    void InitMemoryHelper();
    void EndMemoryHelper();

    template <typename T = void, typename ... Args>
    T* custom_malloc(Args&& ... args)
    {
    #ifndef AK_USE_JAM_MEMORY_SYSTEM
        if(sizeof(T) <= 16)
			return __fixed1.alloc<T>(std::forward<Args>(args)...);
        if(sizeof(T) <= 32)
			return __fixed2.alloc<T>(std::forward<Args>(args)...);
		if(sizeof(T) <= 96)
			return __fixed3.alloc<T>(std::forward<Args>(args)...);
    #endif
        return __jam.alloc<T>(std::forward<Args>(args)...);
    }

    template <typename T = void>
    void custom_free(T* ptr)
    {
    #ifndef AK_USE_JAM_MEMORY_SYSTEM
        if(__fixed1.contains((void*)ptr))
			__fixed1.free(ptr);
		else if(__fixed2.contains((void*)ptr))
			__fixed2.free(ptr);
		else if(__fixed3.contains((void*)ptr))
			__fixed3.free(ptr);
		else if(__jam.contains((void*)ptr))
			__jam.free(ptr);
    #else
		if(__jam.contains((void*)ptr))
			__jam.free(ptr);
    #endif
        else
            Core::log::report(ERROR, "Memory Helper: a pointer allocated by another allocator cannot be freed");
    }
}

#endif // __AK_MEMORY_HELPER__
