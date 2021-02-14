#include <cglm/cglm.h>
#include <GL/glew.h>

#include "graphics.h"
#include "shader.h"
#include "terrain.h"
#include "utils.h"

const float TERRAIN_LENGTH = 100;
static mat4 model_mat;

Terrain *terrain_generated() {
	Terrain *t = xmalloc(sizeof(Terrain));
	t->shader = shader_new("shader/terrain_vertex.glsl", "shader/terrain_fragment.glsl");
	t->vao = vao_new();

	Vertex vertices[] = {
		(Vertex){-TERRAIN_LENGTH / 2, 0.0, -TERRAIN_LENGTH / 2},
		(Vertex){-TERRAIN_LENGTH / 2, 0.0, TERRAIN_LENGTH / 2},
		(Vertex){TERRAIN_LENGTH / 2, 0.0, TERRAIN_LENGTH / 2},
		(Vertex){TERRAIN_LENGTH / 2, 0.0, TERRAIN_LENGTH / 2},
		(Vertex){TERRAIN_LENGTH / 2, 0.0, -TERRAIN_LENGTH / 2},
		(Vertex){-TERRAIN_LENGTH / 2, 0.0, -TERRAIN_LENGTH / 2}
	};

	vao_bind(t->vao);
	vao_vertex_buffer(t->vao, vertices, 6);

	glm_mat4_identity(model_mat);
	glm_rotate(model_mat, glm_rad(90), (vec3){0.0, 1.0, 0.0});

	return t;
}

void terrain_render(Terrain *t, mat4 proj_mat, mat4 view_mat) {
	shader_enable(t->shader);
	shader_load_mat4(t->shader, "proj_mat", proj_mat);
	shader_load_mat4(t->shader, "view_mat", view_mat);
	shader_load_mat4(t->shader, "model_mat", model_mat);

	vao_bind(t->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao_unbind(t->vao);
	shader_disable(t->shader);
}

void terrain_free(Terrain *t) {
	vao_free(t->vao);
	shader_free(t->shader);
	free(t);
}