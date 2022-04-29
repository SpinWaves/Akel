// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/07/2021
// Updated : 29/04/2022

#ifndef __AK_MEMORY_MANAGER__
#define __AK_MEMORY_MANAGER__

#include <Akpch.h>

namespace Ak
{
    class MemoryManager
    {
        private:
            struct ControlUnit
            {
                std::vector<std::weak_ptr<JamAllocator>> jamStack;
                std::vector<std::weak_ptr<FixedAllocator>> fixedStack;
            };

            inline static std::shared_ptr<ControlUnit> control_unit;

        public:
            MemoryManager() = delete;

            static void init();
            static void end();

            static void useMemoryManager(bool set = true);
            inline static bool isMemoryManagerUsed() noexcept { return _use; }

            static std::shared_ptr<ControlUnit>& accessToControlUnit() { return control_unit; }

            template <typename T = void, typename ... Args>
            static T* alloc(Args&& ... args);
            
            template <typename T = void>
            static T* alloc(size_t size);

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
        if(_use && __jam.is_init())
        {
		    if(Core::ProjectFile::getBoolValue("memory_manager_enable_fixed_allocator"))
            {
                if(!std::is_class<T>::value)
                {
                    if(sizeof(T) <= 16)
            			return __fixed1.alloc<T>(std::forward<Args>(args)...);
                    if(sizeof(T) <= 32)
            			return __fixed2.alloc<T>(std::forward<Args>(args)...);
            		if(sizeof(T) <= 96)
            			return __fixed3.alloc<T>(std::forward<Args>(args)...);
                }
            }
            return __jam.alloc<T>(std::forward<Args>(args)...);
        }
        return new T(std::forward<Args>(args)...);
    }

    template <typename T = void>
    T* MemoryManager::alloc(size_t size)
    {
        if(_use && __jam.is_init())
        {
            /*
            if(Core::ProjectFile::getBoolValue("memory_manager_enable_fixed_allocator"))
            {
                if(!std::is_class<T>::value)
                {
                    if(size <= 16)
                        return __fixed1.alloc<T>(std::forward<Args>(args)...);
                    if(size <= 32)
                        return __fixed2.alloc<T>(std::forward<Args>(args)...);
                    if(size <= 96)
                        return __fixed3.alloc<T>(std::forward<Args>(args)...);
                }
            }
            */
            return __jam.alloc<T>(size);
        }
        return new T(size);
    }

    template <typename T = void>
    void MemoryManager::free(T* ptr)
    {
        if(_use)
        {
		    if(Core::ProjectFile::getBoolValue("memory_manager_enable_fixed_allocator"))
            {
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
            }
    		if(__jam.contains((void*)ptr))
            {
    			__jam.free(ptr);
                return;
            }
        }
        for(auto& elem : control_unit->jamStack)
        {
            if(!elem.expired())
            {
                if(elem.lock()->contains(ptr))
                {
                    elem.lock()->free(ptr);
                    return;
                }
            }
        }
        for(auto& elem : control_unit->fixedStack)
        {
            if(!elem.expired())
            {
                if(elem.lock()->contains(ptr))
                {
                    elem.lock()->free(ptr);
                    return;
                }
            }
        }

        ::delete ptr;
    }


    template <typename T = void, typename ... Args>
    inline T* memAlloc(Args&& ... args) { return MemoryManager::alloc<T>(std::forward<Args>(args)...); }

    template <typename T = void>
    inline T* memAlloc(size_t size) { return MemoryManager::alloc<T>(size); }

    template <typename T = void>
    inline void memFree(T* ptr) { MemoryManager::free(ptr); }
}

#endif // __AK_MEMORY_MANAGER__
