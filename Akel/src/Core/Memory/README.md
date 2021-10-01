# JamAllocator
The JamAllocator is a memory optimisation oriented allocator. It is based on the Pool Allocator model but has the particularity of being able to allocate objects like the C++ "new" allocator.
Like many game engine allocators, it is based on a main allocation (the allocator heap) and the allocation requested by the user will take bits of this heap.
The JamAllocator uses a system of flags to describe pruned memory areas and differentiate them from the "pure" area of the heap (the one that has not yet been allocated).
Flags are 16-byte chunks allocated just before the pointer returned to the user. They contain the offset of the pointer in the heap and the size of the memory area that the pointer occupies so that when the pointer is freed, the allocator can know if it can reallocate that memory area for a next pointer.

Akel has an internal safety feature that allows the heap to be freed of all instantiated JamAllocators and FixedAllocators when a FATAL_ERROR is sent to the logs and to the kernel's error handling system (which will cause the program to be stopped in an emergency).

<p align="center">
    <img src="https://github.com/Kbz-8/Akel/blob/dev/Ressources/assets/jam_alloc_diagram.png" alt="drawing" width="500"/>
</p>
