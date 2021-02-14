#include <stddef.h>

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "camera.h"
#include "utils.h"

#define KEY_A 65
#define KEY_D 68
#define KEY_S 83
#define KEY_W 87

const float CAMERA_FACTOR = 5;
static vec3 front, up;

Camera *camera_new() {
	Camera *c = xmalloc(sizeof(Camera));
	glm_vec3_copy((vec3){0.0, 0.0, 3.0}, c->position);
	glm_vec3_copy((vec3){0.0, 0.0, -1.0}, front);
	glm_vec3_copy(GLM_YUP, up);
	glm_mat4_identity(c->view_matrix);
	return c;
}

void camera_update(Camera *c, Window *w, float delta) {
	float camera_speed = CAMERA_FACTOR * delta;
	vec3 target;

	glm_vec3_add(c->position, front, target);
	glm_mat4_identity(c->view_matrix);
	glm_lookat(c->position, target, GLM_YUP, c->view_matrix);

	if (window_key_pressed(w, KEY_W)) {
		vec3 addition;
		glm_vec3_scale(front, camera_speed, addition);
		glm_vec3_add(c->position, addition, c->position);
	}
	if (window_key_pressed(w, KEY_S)) {
		vec3 subtraction;
		glm_vec3_scale(front, camera_speed, subtraction);
		glm_vec3_sub(c->position, subtraction, c->position);
    }
	if (window_key_pressed(w, KEY_A)) {
		vec3 cross, subtraction;
		glm_cross(front, up, cross);
		glm_normalize(cross);
		glm_vec3_scale(cross, camera_speed, subtraction);
		glm_vec3_sub(c->position, subtraction, c->position);
	}
	if (window_key_pressed(w, KEY_D)) {
		vec3 cross, addition;
		glm_cross(front, up, cross);
		glm_normalize(cross);
		glm_vec3_scale(cross, camera_speed, addition);
		glm_vec3_add(c->position, addition, c->position);
	}
}