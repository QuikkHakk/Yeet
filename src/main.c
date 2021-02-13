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
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};
	int vi = 3;

	vao_bind(vao);
	vao_vertex_buffer(vao, vertices, vi);

	if (window == NULL) {
		return EXIT_FAILURE;
	}
	while (!window_should_close(window)) {
		window_update_pre(window);

		shader_enable(shader);
		vao_bind(vao);
		glDrawArrays(GL_TRIANGLES, 0, vi);
		vao_unbind(vao);
		shader_disable(shader);

		window_update_post(window);
	}
	window_close(window);

	vao_free(vao);
	shader_free(shader);

	return EXIT_SUCCESS;
}