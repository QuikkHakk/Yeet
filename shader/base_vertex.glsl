#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture_coords;

out vec2 out_texture_coords;

void main() {
    gl_Position = vec4(in_position, 1.0);
    out_texture_coords = in_texture_coords;
}       