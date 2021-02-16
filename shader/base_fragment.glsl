#version 330 core

in vec2 out_texture_coords;
in vec3 out_normal;
in vec3 out_light_dir;

out vec4 color;

uniform sampler2D in_texture;

void main() {
	
	vec3 normal_unit = normalize(out_normal);
	vec3 light_unit = normalize(out_light_dir);

	float brightness = max(dot(normal_unit, light_unit), 0.0);
	vec3 diffuse = brightness * vec3(1.0);

	color = vec4(diffuse, 1.0) * texture(in_texture, out_texture_coords);
}