// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 03/06/2021

#ifndef __AE_BUFFER__
#define __AE_BUFFER__

#include <AEpch.h>
#include <Platform/platform.h>

namespace AE::GL
{
    class Buffer
    {
        public:
            Buffer(GLenum type);

            void generate();
            void bindBuffer();
            void unbindBuffer();
            void setSize(GLsizeiptr SIZE);

			template <typename T = float>
            void pushData(int start, std::vector<T> &data)
			{
				glBufferSubData(_type, start, data.size(), data.data());
			}
           
		   void deleteBuffer();

           virtual ~Buffer();

        private:
            GLuint _buffer = 0;
            GLenum _type;
    };
}

#endif // __AE_BUFFER__

