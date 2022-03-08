// This file is a part of Akel
// Authors : @kbz_8
// Created : 28/09/2021
// Updated : 07/03/2022

#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 proj;
} ubo;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = ubo.proj * ubo.model * vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
}
