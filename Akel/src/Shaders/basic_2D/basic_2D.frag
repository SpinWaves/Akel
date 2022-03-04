// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/09/2021
// Updated : 04/03/2022

#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(fragColor, 1.0);
}
