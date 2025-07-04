#pragma once
#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTex;

uniform mat4 uM;
uniform mat4 uV;
uniform mat4 uP;

out vec2 TexCoord;

void main()
{
    gl_Position = uP * uV * uM * inPos;
    TexCoord = inTex;
}
