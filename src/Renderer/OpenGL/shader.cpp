// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 14/04/2021

#include <Renderer/renderer.h>
#include <Core/core.h>
#include <Platform/platform.h>

namespace AE::GL
{
    Shader::Shader(AE_text vertexFile, AE_text fragmentFile)
    {
        std::string getter = Core::SoftInfo::getGLinfo();
        if(std::stof(getter) < 2.0)
            messageBox(FATAL_ERROR, "Your version of OpenGL does not support shaders", std::string("You have OpenGL version : " + getter));

        program = glCreateProgram();

        if(!program) 
            messageBox(ERROR, "Unable to create a shader program", SDL_GetError());

        genShader(LoadSourceShader(vertexFile), GL_VERTEX_SHADER); 
        genShader(LoadSourceShader(fragmentFile), GL_FRAGMENT_SHADER);

        glLinkProgram(program); 
        glValidateProgram(program); 
    }

    void Shader::bindShader()
    {
        glUseProgram(program);
    }

    void Shader::unbindShader()
    {
        glUseProgram(0); 
    }

    bool Shader::isBinded()
    {
        int current;
        glGetIntegerv(GL_CURRENT_PROGRAM, &current);
        if(current == program)
            return true;
        return false;
    }

    void Shader::setFloat(const std::string &name, float v)
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), v);
    }

    void Shader::setVec3(const std::string &name, const Maths::Vec3<double> & v)
    {
        glUniform3f(glGetUniformLocation(program, name.c_str()), v.X, v.Y, v.Z);
    }

    void Shader::setVec2(const std::string &name, const Maths::Vec2<double> & v)
    {
        glUniform2f(glGetUniformLocation(program, name.c_str()), v.X, v.Y);
    }

    void Shader::setVec3(const std::string &name, int x, int y, int z)
    {
        glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
    }

    void Shader::setVec2(const std::string &name, int x, int y)
    {
        glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
    }

    void Shader::setInt(const std::string &name, int v)
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), v);
    }

    void Shader::setBool(const std::string &name, bool v)
    {
        glUniform1f(glGetUniformLocation(program, name.c_str()), v);
    }

    void Shader::setVec4(const std::string &name, const Maths::Vec4<double> & v)
    {
        glUniform4f(glGetUniformLocation(program, name.c_str()), v.X, v.Y, v.Z, v.W);
    }

    void Shader::setVec4(const std::string &name, int x, int y, int z, int t)
    {
        glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, t);
    }
    void Shader::setMat4(const std::string &name, glm::mat4 matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }


    char* Shader::LoadSourceShader(AE_text filename)
    {
        char *src = NULL;  
        FILE *fp = NULL;    
        long long SIZE;    
        long i;            
        _filename = filename;


        fp = fopen(filename, "r");
        if(fp == NULL) 
        {
            messageBox(ERROR, "Unable to open a shader code", SDL_GetError());
            return NULL;
        }

        fseek(fp, 0, SEEK_END);
        SIZE = ftell(fp);

        rewind(fp);

        src = new char[SIZE + 1];
        if(src == NULL)
        {
            fclose(fp);
            messageBox(ERROR, "Memory allocation error for a shader", SDL_GetError());
            return NULL;
        }

        for(i = 0; i < SIZE; i++)
            src[i] = fgetc(fp);

        src[SIZE] = '\0'; 

        fclose(fp); 
        std::cout << filename << " : ";
        return src;
    }

    void Shader::genShader(AE_text source, int type)
    {
        shader = glCreateShader(type); 

        if(!shader) 
        {
            messageBox(ERROR, "Unable to create a shader", SDL_GetError());
            return;
        }

        glShaderSource(shader, 1, &source, NULL); 
        glCompileShader(shader); 

        GLint shader_compiled = GL_TRUE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled); 

        if(shader_compiled == GL_FALSE)
        {
            GLsizei logsize = 0;
            char *log = NULL;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);

            log = new char[logsize + 1];
            if(!log)
            {
                messageBox(ERROR, "Memory allocation error for a shader error", SDL_GetError());
                glDeleteShader(shader);
                return;
            }

            memset(log, '\0', logsize + 1);

            glGetShaderInfoLog(shader, logsize, &logsize, log);

            std::string _error = "Shader compilation error : ";
            _error.append(_filename);

            messageBox(ERROR, _error, log);

            delete[] log;

            glDeleteShader(shader);

            return;
        }

        if(type == 35633 && shader)
            std::cout << "Vertex shader made with success" << std::endl;
        if(type == 35632 && shader)
            std::cout << "Fragment shader made with success" << std::endl << std::endl;

        glAttachShader(program, shader);
    }

    Shader::~Shader()
    {
        if(shader)
            glDeleteShader(shader);
        if(program) 
            glDeleteProgram(program);

        unbindShader();
    }
}
