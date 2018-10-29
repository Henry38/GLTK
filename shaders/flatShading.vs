#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

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

// data to geometry shader
out vec3 o_normalView;
out vec3 o_eyeView;

void main()
{
    o_normalView = NormalMatrix * ModelNormalMatrix * normal;
    o_eyeView = (View * ModelMatrix * vec4(position,1.0)).xyz;

    gl_Position = ProjViewMatrix * ModelMatrix * vec4(position, 1.0);
}
