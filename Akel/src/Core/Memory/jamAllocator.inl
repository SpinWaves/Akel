// This file is a part of Akel
// CREATED : 25/07/2021
// UPDATED : 12/12/2021

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
        BinarySearchTree<JamAllocator::flag&> node = _freeSpaces.find(finder);
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

        flag* flag_ptr = nullptr;

        lockThreads(mutex);

        for(auto it = _usedSpaces.begin(); it != _usedSpaces.end(); it++)
        {
            if((ptr >= (void*)(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::flag)) && ptr < (void*)(reinterpret_cast<uintptr_t>(_heap) + (*(it + 1))->offset))
               || (it == _usedSpaces.end() - 1 && ptr >= (void*)(reinterpret_cast<uintptr_t>(_heap) + (*it)->offset + sizeof(JamAllocator::flag))))
            {
                flag_ptr = *it;
                _usedSpaces.erase(it);
                break;
            }
        }
        
        flag_ptr = &_usedSpaces.find();

        if(!flag_ptr)
        {
            Core::log::report(ERROR, "JamAllocator : unable to find the flag of %p", ptr);
            unlockThreads(mutex);
            return;
        }

        size_t sizeType = flag_ptr->size;
        if(_freeSpaces.empty())
        {
            _freeSpaces.push_back(flag_ptr);
            unlockThreads(mutex);
            ptr = nullptr;
            return;
        }
        else if(_freeSpaces.size() >= 10)
        {
            if(sizeType > _freeSpaces[(int)(_freeSpaces.size() / 4)]->size) // If size of flag to move is size is less than the first quarter of the free flags we do a simple iteration
            {
                std::vector<JamAllocator::flag*>::iterator it = _freeSpaces.begin() + (int)(_freeSpaces.size() / 2);
                while(it != _freeSpaces.begin() || it != _freeSpaces.end())
                {
                    if((*it)->size == sizeType)
                    {
                        _freeSpaces.insert(it, flag_ptr);
                        break;
                    }
                    else if((*it)->size > sizeType)
                    {
                        it--;
                        if((*it)->size == sizeType)
                        {
                            _freeSpaces.insert(it, flag_ptr);
                            break;
                        }
                        else if((*it)->size < sizeType)
                        {
                            it++;
                            _freeSpaces.insert(it, flag_ptr);
                            break;
                        }
                    }
                    else if((*it)->size < sizeType)
                    {
                        it++;
                        if((*it)->size == sizeType)
                        {
                            _freeSpaces.insert(it, flag_ptr);
                            break;
                        }
                        else if((*it)->size > sizeType)
                        {
                            it--;
                            _freeSpaces.insert(it, flag_ptr);
                            break;
                        }
                    }
                }
                unlockThreads(mutex);

                ptr = nullptr;
                return;
            }
        }

        for(std::vector<JamAllocator::flag*>::iterator it = _freeSpaces.begin(); it != _freeSpaces.end(); it++)
        {
            if((*it)->size == sizeType)
            {
                _freeSpaces.insert(it, flag_ptr);
                break;
            }
            else if((*it)->size > sizeType)
            {
                if(it == _freeSpaces.begin())
                {
                    _freeSpaces.insert(_freeSpaces.begin(), flag_ptr);
                    break;
                }
                it--;
                _freeSpaces.insert(it, flag_ptr);
                break;
            }
        }

        unlockThreads(mutex);

        ptr = nullptr;
    }
}
