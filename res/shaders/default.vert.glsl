#version 330 core
layout (location = 0) in vec2 a_position;

uniform vec3 u_color;
uniform mat3 u_transform;

out vec3 v_color;

void main()
{
    v_color = u_color;

    vec3 position = u_transform * vec3(a_position, 1.0f);
    gl_Position = vec4(position , 1.0f);
}
