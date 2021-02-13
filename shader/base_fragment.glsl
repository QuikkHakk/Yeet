#version 330 core

in vec2 out_texture_coords;

out vec4 color;

uniform sampler2D in_texture;

void main() {
	color = texture(in_texture, out_texture_coords);
}