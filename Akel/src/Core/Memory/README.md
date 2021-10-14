# JamAllocator
The JamAllocator is a memory optimisation oriented allocator. It is based on the Pool Allocator model but has the particularity of being able to allocate objects like the C++ "new" allocator.
Like many game engine allocators, it is based on a main allocation (the allocator heap) and the allocation requested by the user will take bits of this heap.
The JamAllocator uses a system of flags to describe pruned memory areas and differentiate them from the "pure" area of the heap (the one that has not yet been allocated).
Flags are 16-byte chunks allocated just before the pointer returned to the user. They contain the offset of the pointer in the heap and the size of the memory area that the pointer occupies so that when the pointer is freed, the allocator can know if it can reallocate that memory area for a next pointer.

Akel has an internal safety feature that allows the heap to be freed of all instantiated JamAllocators and FixedAllocators when a FATAL_ERROR is sent to the logs and to the kernel's error core system (which will cause the program to be stopped in an emergency).

<p align="center">
    <img src="https://github.com/SpinWaves/Akel/blob/main/Ressources/assets/jam_alloc_diagram.png" alt="drawing"/>
</p>

```C++
class CustomComponent : public Ak::Component
{
    private:
        MyClass* ptr = nullptr;
        Ak::JamAllocator allocator;

    public:
        void CustomComponent::onAttach() override
        {
            allocator.init(255/*bytes*/);
            ptr = allocator.alloc<MyClass>(/* Args to pass to MyClass constructor */);
        }

        void CustomComponent::onQuit() override
        {
            allocator.free(ptr); // free the pointer
            allocator.destroy();
        }
};
```

# FixedAllocator

The FixedAllocator is an allocation performance oriented allocator. It is based on a system of blocks of the same size that can be allocated individually. Like the JamAllocator it can allocate objects like "new".

<p align="center">
    <img src="https://github.com/SpinWaves/Akel/blob/main/Ressources/assets/fixed_alloc_diagram.png" alt="drawing"/>
</p>

```C++
class CustomComponent : public Ak::Component
{
    private:
        int* ptr = nullptr;
        Ak::FixedAllocator allocator;

    public:
        void CustomComponent::onAttach() override
        {
            allocator.init(8, 1);
            ptr = allocator.alloc<int>();
        }

        void CustomComponent::onQuit() override
        {
            allocator.free(ptr); // free the pointer
            allocator.destroy();
        }
};
```

# Memory Manager
Akel's memory manager is based on two simple functions: Ak::custom_malloc() and Ak::custom_free().
Ak::custom_malloc() allows you to allocate memory as "new" and Ak::custom_free() to free it as "delete".

```C++
class CustomComponent : public Ak::Component
{
    private:
        MyClass* ptr = nullptr;

    public:
        void CustomComponent::onAttach() override
        {
            ptr = Ak::custom_malloc<MyClass>(/* Args to pass to MyClass constructor */);
        }

        void CustomComponent::onQuit() override
        {
            Ak::custom_free(ptr); // free the pointer
        }
};
```

# Smart pointers wrappers
The unique_ptr and shared_ptr of the standard C++ lib have wrappers for JamAllocators and FixedAllocators, however the two work differently.

The shared_ptr use the Ak::make_shared_ptr_w functions which are derived in 3 functions. The first has a second parameter which is a reference to the FixedAllocator which contains the passed pointer (to free it properly when destroying the pointer). The second one has a second parameter, like the first one) but for the JamAllocators. The third one only takes as parameter the pointer to be passed to the shared_ptr. This one will free it via the memory manager and the "custom_free()" function.
It is possible not to pass the allocator which contains the pointer and to use the third function even for pointers not allocated by the memory manager because if this one does not find the pointer among its allocators it will seek in the other instanciated allocators, but that can take more time.

The unique_ptr needs to be declared differently as we need to pass the destructor of the pointer to the instantiation of the unique_ptr (unlike the shared_ptr). To solve this problem Akel has Ak::unique_ptr_w which is an alias to std::unique_ptr with the default destructor of the memory manager.
Akel also has a function to create a unique_ptr_w which is Ak::make_unique_ptr_w and which takes as argument a simple pointer to contain.

```C++
class CustomComponent : public Ak::Component
{
    private:
        std::shared_ptr<MyClass> s_ptr;
        Ak::unique_ptr_w<MyClass> u_ptr;

    public:
        void CustomComponent::onAttach() override
        {
            s_ptr = Ak::make_shared_ptr_w<MyClass>(Ak::custom_malloc<MyClass>(/* Args to pass to MyClass constructor */));
            u_ptr = Ak::make_unique_ptr_w<MyClass>(Ak::custom_malloc<MyClass>(/* Args to pass to MyClass constructor */));
        }
};
```
