// This file is a part of Akel
// Author : @kbz_8
// CREATED : 28/09/2021
// UPDATED : 28/09/2021

#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(fragColor, 1.0);
}
