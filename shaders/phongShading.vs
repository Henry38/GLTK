#version 330 core

// vertex attribut
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

// uniform input
uniform mat4 view;
uniform mat4 mvp;
uniform mat3 normal_mat;

// data to fragment shader
out vec3 normalView;
out vec3 eyeView;

void main()
{
    normalView = normalize(normal_mat * normal);
    eyeView = normalize(view * vec4(position,1.0)).xyz;

    gl_Position = mvp * vec4(position, 1.0);
}
