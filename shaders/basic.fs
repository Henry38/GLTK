#version 330 core

in vec3 n;

uniform vec3 dir_light;
uniform vec3 color;

out vec4 outColor;

void main()
{
    vec3 unit_n = normalize(n);
    float d = max(-dot(unit_n, dir_light), 0.0);
    outColor = d * vec4(color, 1.0);
}
