// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 26/12/2021

#include <Core/Memory/jamAllocator.h>
#include <Core/log.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_heap == nullptr)
        {
            Core::log::report(FATAL_ERROR, "Jam Allocator: you need to initialize the allocator before aking him to give you memory");
            return nullptr;
        }
        size_t sizeType = sizeof(T);
        if(!canHold(sizeType))
        {
            if(_autoResize)
                increase_size(_heapSize * (4/3));
            else
            {
                Core::log::report(FATAL_ERROR, "Jam Allocator: the requested allocation is too large for the allocator, free up memory or increase the size of the allocator");
                return nullptr;
            }
        }

        T* ptr = nullptr;

        lockThreads(mutex);

        JamAllocator::flag finder;
        finder.size = sizeType;
        finder.offset = 0;
        BinarySearchTree<JamAllocator::flag&>* node = _freeSpaces.find(finder);
        if(node != nullptr)
        {
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + node->getData().offset + sizeof(JamAllocator::flag));
            _usedSpaces.add(node->getData());
            _freeSpaces.remove(finder);
        }
        if(ptr == nullptr) // If we haven't found free flag
        {
            JamAllocator::flag* flag_ptr = static_cast<flag*>((void*)(reinterpret_cast<uintptr_t>(_heap) + _memUsed)); // We create a new flag
            flag_ptr->size = sizeType;
            flag_ptr->offset = _memUsed;
            _usedSpaces.add(*flag_ptr);
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed + sizeof(JamAllocator::flag));
            _memUsed += sizeType + sizeof(JamAllocator::flag);
        }

        unlockThreads(mutex);

        if(std::is_class<T>::value)
            new ((void*)ptr) T(std::forward<Args>(args)...);

    	return ptr;
    }

    template <typename T = void>
    void JamAllocator::free(T* ptr)
    {
        if(ptr == nullptr)
        {
            Core::log::report(WARNING, "Jam Allocator: you cannot free a nullptr");
            return;
        }
        if(_heap == nullptr)
        {
            Core::log::report(WARNING, "Jam Allocator: trying to free a pointer with an uninitialised allocator (the pointer will be free by 'delete')");
            delete ptr;
            return;
        }
        if(!contains((void*)ptr))
        {
            Core::log::report(WARNING, "Jam Allocator: a pointer allocated by another allocator will be freed, this may be an error (the pointer will be free by 'delete')");
            delete ptr;
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        flag flag_ref;

        lockThreads(mutex);

        for(auto it = _usedSpaces.root_it(); it.hasNext(); it.next())
        {
            if((ptr >= (void*)(reinterpret_cast<uintptr_t>(_heap) + (*it).getData().offset + sizeof(JamAllocator::flag)) && ptr < (void*)(reinterpret_cast<uintptr_t>(_heap) + it.forward_next().getData().offset))
               || (it.hasNext() == false && ptr >= (void*)(reinterpret_cast<uintptr_t>(_heap) + (*it).getData().offset + sizeof(JamAllocator::flag))))
            {
                flag_ref.size = (*it).getData().size;
                flag_ref.offset = (*it).getData().offset;
                _usedSpaces.remove(it.get_node());
                break;
            }
        }
        
        if(flag_ref.size == 0 && flag_ref.offset == 0)
        {
            Core::log::report(ERROR, "JamAllocator : unable to find the flag of %p", ptr);
            unlockThreads(mutex);
            return;
        }

        _freeSpaces.add(flag_ref);
        unlockThreads(mutex);
        ptr = nullptr;
    }
}
