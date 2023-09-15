// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/07/2021
// Updated : 15/09/2023

#ifndef __AK_SHARED_PTR__
#define __AK_SHARED_PTR__

#include <Akpch.h>
#include <Core/Memory/memoryManager.h>

namespace Ak
{
	template <typename T>
	class AK_API SharedPtr
	{
		public:
			explicit SharedPtr(T* ptr = nullptr) noexcept;
			SharedPtr(const SharedPtr& other) noexcept;
			SharedPtr(SharedPtr&& other) noexcept;
			SharedPtr& operator=(std::nullptr_t other) noexcept;
			SharedPtr& operator=(const SharedPtr& other) noexcept;
			SharedPtr& operator=(SharedPtr&& other) noexcept;
			operator bool() const noexcept;
			bool operator==(const SharedPtr& other) noexcept;
			bool operator==(T* ptr) noexcept;
			T& operator*() noexcept;
			T* operator->() noexcept;
			T* get() noexcept;
			void swap(SharedPtr& other) noexcept;
			void reset(T* ptr = nullptr) noexcept;
			~SharedPtr();

		private:
			struct RefCount
			{
				std::atomic<int> shared = 0;
				std::atomic<int> weak = 0;

				RefCount(int s, int w) : shared(s), weak(w) {}
			};
		private:
			inline static std::unordered_map<void*, RefCount*> _refs;
			T* _ptr = nullptr;
			RefCount* _ref = nullptr;
	};

    template <typename T>
    inline std::shared_ptr<T> make_shared_ptr_w(T* ptr) { return std::shared_ptr<T>(ptr, [](T* ptr) { memFree(ptr); }); }

    template <typename T = void, typename ... Args>
    inline std::shared_ptr<T> create_shared_ptr_w(Args&& ... args) noexcept { return make_shared_ptr_w<T>(memAlloc<T>(std::forward<Args>(args)...)); }
}

#include <Core/Memory/akel_shared_ptr.inl>

#endif
