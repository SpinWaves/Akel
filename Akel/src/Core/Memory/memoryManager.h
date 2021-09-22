// This file is a part of Akel
// CREATED : 23/07/2021
// UPDATED : 22/09/2021

#ifndef __AK_MEMORY_MANAGER__
#define __AK_MEMORY_MANAGER__

#include <Akpch.h>
#include <Modules/modules.h>

namespace Ak
{
    class MemoryManager
    {
        private:
            struct ControlUnit
            {
                std::vector<JamAllocator*> jamStack;
                std::vector<FixedAllocator*> fixedStack;
            };

            inline static std::shared_ptr<ControlUnit> control_unit;

        public:
            MemoryManager() = delete;

            static void init();
            static void end();

            static void useMemoryManager(bool set = true);
            static bool isMemoryManagerUsed();

            static std::shared_ptr<ControlUnit> accessToControlUnit();

            template <typename T = void, typename ... Args>
            static T* alloc(Args&& ... args);

            template <typename T = void>
            static void free(T* ptr);

            ~MemoryManager() = delete;

        private:
            inline static JamAllocator __jam;
            inline static FixedAllocator __fixed1;
            inline static FixedAllocator __fixed2;
            inline static FixedAllocator __fixed3;
            inline static bool _use = true;
    };

    template <typename T = void, typename ... Args>
    T* MemoryManager::alloc(Args&& ... args)
    {
		if(Core::ProjectFile::getBoolValue("use_memory_manager"))
        {
            #ifndef AK_USE_JAM_MEMORY_SYSTEM
                if(!std::is_class<T>::value)
                {
                    if(sizeof(T) <= 16)
            			return __fixed1.alloc<T>(std::forward<Args>(args)...);
                    if(sizeof(T) <= 32)
            			return __fixed2.alloc<T>(std::forward<Args>(args)...);
            		if(sizeof(T) <= 96)
            			return __fixed3.alloc<T>(std::forward<Args>(args)...);
                }
            #endif
            return __jam.alloc<T>(std::forward<Args>(args)...);
        }
        return new T(std::forward<Args>(args)...);
    }

    template <typename T = void>
    void MemoryManager::free(T* ptr)
    {
		if(Core::ProjectFile::getBoolValue("use_memory_manager"))
        {
            #ifndef AK_USE_JAM_MEMORY_SYSTEM
                if(__fixed1.contains((void*)ptr))
                {
        			__fixed1.free(ptr);
                    return;
                }
        		if(__fixed2.contains((void*)ptr))
                {
        			__fixed2.free(ptr);
                    return;
                }
        		if(__fixed3.contains((void*)ptr))
                {
        			__fixed3.free(ptr);
                    return;
                }
            #endif
    		if(__jam.contains((void*)ptr))
            {
    			__jam.free(ptr);
                return;
            }
        }
        for(auto elem : control_unit->jamStack)
        {
            if(elem->contains(ptr))
            {
                elem->free(ptr);
                return;
            }
        }
        for(auto elem : control_unit->fixedStack)
        {
            if(elem->contains(ptr))
            {
                elem->free(ptr);
                return;
            }
        }

        delete ptr;
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

#endif // __AK_MEMORY_MANAGER__
