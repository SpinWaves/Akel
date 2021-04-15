// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 14/04/2021

#ifndef __GL_SHADER__
#define __GL_SHADER__

#include <Maths/maths.h>
#include <AEpch.h>
#include <Utils/utils.h>

namespace AE::GL
{
    class Shader
    {
        public:
            Shader(AE_text vertexFile, AE_text fragmentFile);

            void bindShader(); 
            void unbindShader(); 
            bool isBinded();

            // Modifiers
            void setFloat(const std::string &name, float v);
            void setInt(const std::string &name, int v);
            void setBool(const std::string &name, bool v);
            void setVec3(const std::string &name, const Maths::Vec3<double> &v);
            void setVec2(const std::string &name, const Maths::Vec2<double> &v);
            void setVec4(const std::string &name, const Maths::Vec4<double> &v);
            void setVec3(const std::string &name, int x, int y, int z);
            void setVec2(const std::string &name, int x, int y);
            void setVec4(const std::string &name, int x, int y, int z, int t);
            void setMat4(const std::string &name, glm::mat4 matrix);

            virtual ~Shader();

            GLuint program;

        private:
            std::string LoadSourceShader(AE_text filename);
            void genShader(AE_text source, int type);

            int shader;

            AE_text _filename;
    };
}

#endif // __GL_SHADER__