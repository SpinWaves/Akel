// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 30/04/2021

#ifndef __BUFFER__
#define __BUFFER__

#include <AEpch.h>
#include <Utils/utils.h>

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
				if(glIsBuffer(_buffer) == GL_TRUE)
					glBufferSubData(_type, start, data.size(), data.data());
		    }
           
		   void deleteBuffer();

            virtual ~Buffer();

        private:
            GLuint _buffer = 0;
            GLenum _type;
    };
}

#endif // __BUFFER__
