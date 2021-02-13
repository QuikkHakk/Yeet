#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics.h"
#include "shader.h"
#include "vao.h"
#include "window.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	Window* window = window_new("Yeet Test", WIDTH, HEIGHT);
	VAO *vao = vao_new();
	Shader *shader = shader_new("shader/base_vertex.glsl", "shader/base_fragment.glsl");
	Vertex vertices[] = {
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
	};
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	Texture *texture = texture_new("resources/dirt.png");
	float texture_coords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	int txc_count = 8;
	int indices_count = 6;
	int vi = 4;

	vao_bind(vao);
	vao_vertex_buffer(vao, vertices, vi);
	vao_texture_buffer(vao, texture_coords, txc_count);
	vao_index_buffer(vao, indices, indices_count);

	if (window == NULL) {
		return EXIT_FAILURE;
	}
	while (!window_should_close(window)) {
		window_update_pre(window);

		texture_bind(texture);
		shader_enable(shader);
		vao_bind(vao);
		glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
		vao_unbind(vao);
		shader_disable(shader);

		window_update_post(window);
	}
	window_close(window);

	vao_free(vao);
	shader_free(shader);
	texture_free(texture);

	return EXIT_SUCCESS;
}