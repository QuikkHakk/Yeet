#include <stdio.h>
#include <stdlib.h>

#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "camera.h"
#include "graphics.h"
#include "shader.h"
#include "terrain.h"

const float FOV = 90;
const float FAR = 100;
const float NEAR = 0.1;
const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	Window* window = window_new("Yeet Test", WIDTH, HEIGHT);
	Shader *shader = shader_new("shader/base_vertex.glsl", "shader/base_fragment.glsl");
	Model *model = model_load("resources/stall.obj", "resources/stall.png");
	Terrain *terrain = terrain_generated();
	Camera *camera = camera_new(window);
	mat4 proj_mat, model_mat;
	float last_time = 0.0, delta = 0.0;

	if (window == NULL) {
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, WIDTH, HEIGHT);

	glm_perspective(FOV, WIDTH / HEIGHT, NEAR, FAR, proj_mat);

	while (!window_should_close(window)) {
		float time_now;

		window_update_pre(window);
		
		time_now = glfwGetTime();
		delta = time_now - last_time;
		last_time = time_now;

		camera_update(camera, window, delta);

		terrain_render(terrain, proj_mat, camera->view_matrix);

		glm_mat4_identity(model_mat);

		shader_enable(shader);
		shader_load_mat4(shader, "proj_mat", proj_mat);
		shader_load_mat4(shader, "view_mat", camera->view_matrix);
		shader_load_mat4(shader, "model_mat", model_mat);

		model_render(model);

		shader_disable(shader);

		window_update_post(window);
	}
	window_close(window);

	shader_free(shader);
	model_free(model);
	terrain_free(terrain);

	return EXIT_SUCCESS;
}