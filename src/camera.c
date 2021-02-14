#include <stddef.h>

#include <cglm/cglm.h>

#include "camera.h"
#include "utils.h"

Camera *camera_new() {
	Camera *c = xmalloc(sizeof(Camera));
	glm_vec3_copy((vec3){0.0, 0.0, 3.0}, c->position);
	glm_vec3_copy((vec3){0.0, 0.0, 0.0}, c->target);
	glm_mat4_identity(c->view_matrix);
	return c;
}

void camera_update(Camera *c) {
	glm_mat4_identity(c->view_matrix);
	glm_lookat(c->position, c->target, GLM_YUP, c->view_matrix);
}