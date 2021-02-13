#include <stdlib.h>

#include <GL/glew.h>

#include "graphics.h"
#include "utils.h"
#include "vao.h"

VAO *vao_new() {
	VAO *vao = xmalloc(sizeof(VAO));
	vao->vertex_buffer = NULL;
	
	glGenVertexArrays(1, &vao->id);
	glBindVertexArray(vao->id);
	return vao;
}

void vao_bind(VAO *vao) {
	glBindVertexArray(vao->id);
}

void vao_unbind(VAO *vao) {
	glBindVertexArray(0);
}

void vao_vertex_buffer(VAO *vao, Vertex vertices[], int vertices_count) {
	glGenBuffers(1, &vao->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vao->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
}

void vao_free(VAO *vao) {
	if (vao->vertex_buffer != NULL) {
		glDeleteBuffers(1, &vao->vertex_buffer);
	}
	glDeleteVertexArrays(1, &vao->id);
	free(vao);
}