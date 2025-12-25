#version 330 core
layout (location = 0) in vec2 a_position;

uniform float u_angle;

vec2 rotate(vec2 position, float angle) {
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    vec2 rotated_pos;
    rotated_pos.x = position.x * cos_angle - position.y * sin_angle;
    rotated_pos.y = position.x * sin_angle + position.y * cos_angle;

    return rotated_pos;
}

void main()
{
    gl_Position = vec4(rotate(a_position, u_angle), 0.0, 1.0);
}
