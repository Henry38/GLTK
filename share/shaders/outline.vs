#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;

layout(std140) uniform transform
{
    mat4 ModelMatrix;
    mat3 ModelNormalMatrix;
};

layout(std140) uniform camera
{
    mat4 View;
    mat4 Projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

void main()
{
    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
