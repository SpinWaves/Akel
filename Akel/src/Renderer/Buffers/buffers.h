// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/03/2022
// Updated : 25/03/2022

#ifndef __AK_BUFFERS__
#define __AK_BUFFERS__

#include <Akpch.h>

namespace Ak
{
	class Buffer
	{
		public:
			Buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, const void *data = nullptr);
        	
        	inline void* getPointerMap() const noexcept { return _ptr; }
        	inline VkDeviceSize getSize() const noexcept { return _size; }
        	inline VkDeviceSize getOffset() const noexcept { return _offset; }
        	inline const VkBuffer& getNativeBuffer() const noexcept { return _buffer; }
        	inline const VkDeviceMemory& getDeviceMemory() const noexcept { return _memory; }

        	inline bool operator==(Buffer const& buffer) noexcept
        	{
        		return memory == buffer.getDeviceMemory() && offset == buffer.getOffset() && size == buffer.getSize() && ptr == buffer.getPointerMap() ? true : false;
        	}

        	void mapMemory(void** data) const;
			void unmapMemory() const;

        	~Buffer();

	    private:
	        VkDeviceMemory _memory = VK_NULL_HANDLE;
	        VkDeviceSize _offset = 0;
	        VkDeviceSize _size = 0;
	        VkBuffer _buffer = VK_NULL_HANDLE;
	        void* _ptr = nullptr;
	};
}

#endif // __AK_BUFFERS__
