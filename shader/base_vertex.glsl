#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture_coords;

out vec2 out_texture_coords;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

void main() {
    gl_Position = proj_mat * view_mat * model_mat * vec4(in_position, 1.0);
    out_texture_coords = in_texture_coords;
}       