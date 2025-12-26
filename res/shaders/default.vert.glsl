#version 330 core
layout (location = 0) in vec2 a_position;

uniform mat3 u_transform;

void main()
{
    vec3 position = u_transform * vec3(a_position, 0.0f);
    gl_Position = vec4(position , 1.0f);
}
