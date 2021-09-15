// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 15/09/2021

#include <Core/Memory/jamAllocator.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* JamAllocator::alloc(Args&& ... args)
    {
        if(_heapSize == 0)
        {
            Core::log::report(ERROR, "Jam Allocator: you need to initialize the allocator before aking him to give you memory");
            return nullptr;
        }
        size_t sizeType = sizeof(T);
        if(!canHold(sizeType))
        {
            if(_autoResize)
                resize(_heapSize * (4/3));
            else
            {
                Core::log::report(ERROR, "Jam Allocator: the requested allocation is too large for the allocator, free up memory or increase the size of the allocator");
                return nullptr;
            }
        }

        T* ptr = nullptr;

        lockThreads(mutex);

        /**
         * Start looking in the middle of the vector and go down to find the best
         * size if the pointed block is too big or up if the pointed block is too small
         */
        std::vector<block*>::iterator it = _freeSpaces.begin() + _freeSpaces.size() / 2;
        while(it != _freeSpaces.end() || it != _freeSpaces.begin())
        {
            if((*it)->size == sizeType) // We found a perfect sized block !
            {
                ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::block));
                break;
            }
            else if((*it)->size > sizeType)
            {
                it--;
                if((*it)->size == sizeType)
                {
                    ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::block));
                    break;
                }
                else if((*it)->size < sizeType)
                {
                    it++;
                    ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::block));
                    break;
                }
            }
            else if((*it)->size < sizeType)
            {
                it++;
                if((*it)->size == sizeType)
                {
                    ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::block));
                    break;
                }
                else if((*it)->size > sizeType)
                {
                    it--;
                    ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::block));
                    break;
                }
            }
        }

        if(ptr == nullptr) // If we haven't found free block
        {
            JamAllocator::block* block_ptr = static_cast<block*>((void*)(reinterpret_cast<uintptr_t>(_heap) + _memUsed)); // We create a new block
            block_ptr->size = sizeType;
            block_ptr->offset = _memUsed;
            _usedSpaces.push_back(block_ptr);
            ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _memUsed + sizeof(JamAllocator::block));
            _memUsed += sizeType + sizeof(JamAllocator::block);
        }

        unlockThreads(mutex);

        if(std::is_class<T>::value)
            ::new ((void*)ptr) T(std::forward<Args>(args)...);

    	return ptr;
    }

    template <typename T = void>
    void JamAllocator::free(T* ptr)
    {
        if(!contains((void*)ptr))
        {
            Core::log::report(WARNING, "Jam Allocator: a pointer allocated by another allocator will be freed, this may be an error");
            delete ptr;
            return;
        }
        if(std::is_class<T>::value)
            ptr->~T();

        block* block_ptr = nullptr;

        lockThreads(mutex);

        for(int i = 0; i < _usedSpaces.size(); i++)
        {
            if(ptr == (void*)((uintptr_t)_usedSpaces[i] + sizeof(JamAllocator::block)))
            {
                block_ptr = _usedSpaces[i];
                _usedSpaces.erase(_usedSpaces.begin() + i);
                break;
            }
        }

        size_t size = block_ptr->size;
        if(size > _freeSpaces[_freeSpaces.size() / 4]->size) // If size of block to move is size is less than the first quarter of the free blocks we do a simple iteration
        {
            std::vector<block*>::iterator it = _freeSpaces.begin() + _freeSpaces.size() / 2;
            while(it != _freeSpaces.begin() || it != _freeSpaces.end())
            {
                if((*it)->size == size)
                {
                    _freeSpaces.insert(it, block_ptr);
                    break;
                }
                else if((*it)->size > size)
                {
                    it--;
                    if((*it)->size == size)
                    {
                        _freeSpaces.insert(it, block_ptr);
                        break;
                    }
                    else if((*it)->size < size)
                    {
                        it++;
                        _freeSpaces.insert(it, block_ptr);
                        break;
                    }
                }
                else if((*it)->size < size)
                {
                    it++;
                    if((*it)->size == size)
                    {
                        _freeSpaces.insert(it, block_ptr);
                        break;
                    }
                    else if((*it)->size > size)
                    {
                        it--;
                        _freeSpaces.insert(it, block_ptr);
                        break;
                    }
                }
            }
        }
        else
        {
            for(auto it = _freeSpaces.begin(); it < _freeSpaces.end(); it++)
            {
                if((*it)->size == size)
                {
                    _freeSpaces.insert(it, block_ptr);
                    break;
                }
                else if((*it)->size > size)
                {
                    it--;
                    _freeSpaces.insert(it, block_ptr);
                    break;
                }
            }
        }

        unlockThreads(mutex);

        ptr = nullptr;
    }
}
