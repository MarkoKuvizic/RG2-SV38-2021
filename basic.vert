#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTex;

uniform mat4 uM;
uniform mat4 uV;
uniform mat4 uP;
uniform float uTime;
uniform vec3 uPivot;

out vec2 TexCoord;

void main()
{
    float angle = uTime * 0.2;

    mat4 rotationY = mat4(
    cos(angle), -sin(angle),  0.0,  0.0,
    sin(angle),  cos(angle),  0.0,  0.0,
         0.0,         0.0,    1.0,  0.0,
         0.0,         0.0,    0.0,  1.0
    );

    vec4 pos = vec4(inPos - uPivot, 1.0);
    pos = rotationY * pos;
    pos.xyz += uPivot;

    gl_Position = uP * uV * uM * pos;
    TexCoord = inTex;
}
