#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texture_coords;
layout (location = 2) in vec3 in_normal;

out vec2 out_texture_coords;
out vec3 out_normal;
out vec3 out_light_dir;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

uniform vec3 ulight_pos;

void main() {
    vec4 world_pos = model_mat * vec4(in_position, 1.0);

    gl_Position = proj_mat * view_mat * world_pos;
    out_texture_coords = in_texture_coords;

    out_normal = (model_mat * vec4(in_normal, 1.0)).xyz;
    out_light_dir = ulight_pos - world_pos.xyz;
}       