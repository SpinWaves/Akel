// This file is a part of AtlasEngine
// CREATED : 27/04/2021
// UPDATED : 27/04/2021

#ifndef __ERRORS__
#define __ERRORS__

// GPU
#define AE_CATCH_VK_VERSION_INFO            "Vulkan version : this information can only be obtained by vulkan"
#define AE_CATCH_GPU_VENDOR_INFO            "GPU vendor : there is no context or instance that can get this information"
#define AE_CATCH_NUM_DEVICES_INFO           "GPU devices : this information can only be obtained by vulkan"

// CPU
#define AE_CATCH_CPU_VENDOR_INFO            "Unexpected vendor id"

// GLOBAL
#define AE_CATCH_GL_CONTEXT_CREATION        std::string("OpenGL context : " + std::string(reinterpret_cast<AE_text>(glewGetErrorString(GLEWerr))))

// VK
#define AE_CATCH_VK_INSTANCE_CREATION       "Vulkan instance : unable to create vulkan instance"

// GL
#define AE_CATCH_GL_SHADER_COMPATIBILITY    std::string("You have OpenGL version : " + std::to_string(gpuinfo.getOpenGLversion()))
#define AE_CATCH_GL_SHADER_OPEN_SOURCE      std::string(strerror(errno))
#define AE_CATCH_GL_BUFFER_GENERATION       std::string(reinterpret_cast<AE_text>(glewGetErrorString(glIsBuffer(_buffer))))

// WINDOW
#define AE_CATCH_WIN_TYPE                   "Window type : bad window type"
#define AE_CATCH_WIN_SETTING                "Window setting : no such setting"

#endif // __ERRORS__
