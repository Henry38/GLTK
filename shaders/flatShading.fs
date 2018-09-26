#version 330 core

layout(std140) uniform transform
{
    mat4 ModelMatrix;
};

layout(std140) uniform material
{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    vec4 emptyColor;
    float shininess;
};

layout(std140) uniform camera
{
    mat4 view;
    mat4 projection;
    mat4 ProjViewMatrix;
    mat3 NormalMatrix;
};

// data from geometry shader
in vec3 normalView;
in vec3 eyeView;

// uniform input
uniform vec3 dir_light;

out vec4 outColor;

void main()
{
    // normal / view and light directions (in camera space)
    vec3 n = normalize(normalView);
    vec3 e = normalize(eyeView);
    vec3 l = normalize(NormalMatrix * dir_light);

    // diffuse and specular components of the phong shading model
    float diff = max(-dot(l,n),0.0);
    float spec = pow(max(-dot(reflect(l,n),e),0.0),shininess);

    //vec3 l = normalize(dir_light);
    //float d = max(-dot(n, l), 0.0);

    outColor = ambientColor + (diff * diffuseColor) + (spec * specularColor);
    //outColor = d * diffuseColor;
}
