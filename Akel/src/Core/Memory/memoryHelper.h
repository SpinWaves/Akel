// This file is a part of Akel
// CREATED : 23/07/2021
// UPDATED : 01/08/2021

#ifndef __AK_MEMORY_HELPER__
#define __AK_MEMORY_HELPER__

#include <Akpch.h>

namespace Ak
{
    class MemoryManager
    {
        public:
            MemoryManager() = default;

            static void init();
            static void end();

            template <typename T = void, typename ... Args>
            static T* alloc(Args&& ... args);

            template <typename T = void>
            static void free(T* ptr);

            ~MemoryManager() = default;
        private:
            inline static JamAllocator __jam;
            inline static FixedAllocator __fixed1;
            inline static FixedAllocator __fixed2;
            inline static FixedAllocator __fixed3;
    };

    template <typename T = void, typename ... Args>
    T* MemoryManager::alloc(Args&& ... args)
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
    void MemoryManager::free(T* ptr)
    {
    #ifndef AK_USE_JAM_MEMORY_SYSTEM
        if(__fixed1.contains((void*)ptr))
			__fixed1.free(ptr);
		else if(__fixed2.contains((void*)ptr))
			__fixed2.free(ptr);
		else if(__fixed3.contains((void*)ptr))
			__fixed3.free(ptr);
    #endif
		if(__jam.contains((void*)ptr))
			__jam.free(ptr);
        else
            Core::log::report(ERROR, "Memory Helper: a pointer allocated by another allocator cannot be freed");
    }


    template <typename T = void, typename ... Args>
    T* custom_malloc(Args&& ... args)
    {
        return MemoryManager::alloc<T>(std::forward<Args>(args)...);
    }

    template <typename T = void>
    void custom_free(T* ptr)
    {
        MemoryManager::free(ptr);
    }
}

#endif // __AK_MEMORY_HELPER__
