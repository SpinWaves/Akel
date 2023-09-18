// This file is a part of Akel
// Authors : @kbz_8
// Created : 18/09/2023
// Updated : 18/09/2023

#ifndef __AK_THREAD_SAFE_QUEUE__
#define __AK_THREAD_SAFE_QUEUE__

#include <Akpch.h>

namespace Ak
{
	template <typename T>
	class TSafeQueue
	{
		public:
			TSafeQueue() = default;
			inline T& front()
			{
				std::lock_guard<std::mutex> lock(_mutex);
				return _queue.front();
			}
			inline T& back()
			{
				std::lock_guard<std::mutex> lock(_mutex);
				return _queue.back();
			}
			inline size_t size()
			{
				std::lock_guard<std::mutex> lock(_mutex);
				return _queue.size();
			}
			template <class ... Args>
			inline decltype(auto) emplace(Args&& ... args)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				return _queue.emplace(std::forward<Args>(args)...);
			}
			inline bool empty()
			{
				std::lock_guard<std::mutex> lock(_mutex);
				return _queue.empty();
			}
			inline void pop()
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_queue.pop();
			}
			inline void push(const T& item)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_queue.push(item);
			}
			inline void push(T&& item)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_queue.push(std::move(item));
			}
			~TSafeQueue() = default;

		private:
			std::queue<T> _queue;
			std::mutex _mutex;
	};
}

#endif
