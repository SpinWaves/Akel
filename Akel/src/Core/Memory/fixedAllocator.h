// This file is a part of the Akel editor
// CREATED : 18/07/2021
// UPDATED : 24/07/2021

#ifndef __AK_FIXED_ALLOCATOR__
#define __AK_FIXED_ALLOCATOR__

#include <Akpch.h>
#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak
{
    namespace internalFixed
    {
        static MutexHandel mutex;
    }

    class FixedAllocator
    {
        public:
            FixedAllocator() = default;

            void init(size_t blockSize, size_t numBlocks);
            void resize(size_t numBlocks);
            bool canAlloc();
            bool contains(void* ptr) const;
            void autoResize(bool set);
            void destroy();

            template <typename T = void, typename ... Args>
            T* alloc(Args&& ... args)
            {
                if(!canAlloc())
                {
                    if(_autoResize)
                        resize(_bits.size() * 2);
                    else
                    {
                        Core::log::report(ERROR, "Fixed Allocator: unable to alloc block, no more block free");
                        return nullptr;
                    }
                }
                lockThreads(internalFixed::mutex);

                *_it = true;

                if(std::is_class<T>::value)
                {
                    T* ptr = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * (std::distance(_it, _bits.rend()) - 1));
                    unlockThreads(internalFixed::mutex);
                    new ((void*)ptr) T(std::forward<Args>(args)...);

                    return ptr;
                }

                unlockThreads(internalFixed::mutex);

                return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(_heap) + _block_size * (std::distance(_it, _bits.rend()) - 1));
            }

            template <typename T = void>
            void free(T* ptr)
            {
                if(!contains(ptr))
                {
                    Core::log::report(ERROR, "Fixed Allocator: a pointer allocated by another allocator cannot be freed");
                    return;
                }
                lockThreads(internalFixed::mutex);

                if(std::is_class<T>::value)
                    ptr->~T();

                const size_t index = (reinterpret_cast<uintptr_t>(ptr) - reinterpret_cast<uintptr_t>(_heap)) / _block_size;
                _bits[index] = false;

                unlockThreads(internalFixed::mutex);
            }

            ~FixedAllocator();

        private:
            size_t _block_size = 0;
            void* _heap = nullptr;
        	size_t _heap_size = 0;
            std::vector<bool> _bits;
            bool _autoResize = false;
            std::vector<bool>::reverse_iterator _it;
    };
}

#endif // __AK_FIXED_ALLOCATOR__
