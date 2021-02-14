#include <stdio.h>
#include <stdlib.h>

#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "camera.h"
#include "graphics.h"
#include "shader.h"
#include "vao.h"

const float FOV = 90;
const float FAR = 100;
const float NEAR = 0.1;
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
	Texture *texture = texture_new("resources/container.jpg");
	Camera *camera = camera_new();
	float texture_coords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	int txc_count = 8;
	int indices_count = 6;
	int vi = 4;
	mat4 proj_mat, model_mat;
	float last_time = 0.0, delta = 0.0;

	if (window == NULL) {
		return EXIT_FAILURE;
	}

	vao_bind(vao);
	vao_vertex_buffer(vao, vertices, vi);
	vao_texture_buffer(vao, texture_coords, txc_count);
	vao_index_buffer(vao, indices, indices_count);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, WIDTH, HEIGHT);

	glm_perspective(FOV, WIDTH / HEIGHT, NEAR, FAR, proj_mat);

	while (!window_should_close(window)) {
		float time_now;

		window_update_pre(window);
		
		time_now = glfwGetTime();
		delta = time_now - last_time;
		last_time = time_now;

		camera_update(camera, window, delta);

		glm_mat4_identity(model_mat);
		glm_rotate(model_mat, glfwGetTime(), (vec3){0.0, 1.0, 0.0});

		texture_bind(texture);
		shader_enable(shader);
		shader_load_mat4(shader, "proj_mat", proj_mat);
		shader_load_mat4(shader, "view_mat", camera->view_matrix);
		shader_load_mat4(shader, "model_mat", model_mat);

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