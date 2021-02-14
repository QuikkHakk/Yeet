#include <stdio.h>

#include <cglm/cglm.h>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stretchy_buffer.h"

#include "graphics.h"
#include "utils.h"

Texture *texture_new(const char *texture_path) {
	Texture *t = xmalloc(sizeof(Texture));
	int width, height, nrChannels;
	unsigned char *data;
	
	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
	glGenTextures(1, &t->id);
	glBindTexture(GL_TEXTURE_2D, t->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		fprintf(stderr, "Failed to load texture file %s!\n", texture_path);
		exit(EXIT_FAILURE);
	}

	stbi_image_free(data);

	return t;
}

void texture_bind(Texture *t) {
	glBindTexture(GL_TEXTURE_2D, t->id);
}

void texture_free(Texture *t) {
	glDeleteTextures(1, &t->id);
	free(t);
}

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void vao_texture_buffer(VAO *vao, UV texture_coords[], int txc_count) {
	glGenBuffers(1, &vao->texture_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vao->texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, txc_count * sizeof(UV), texture_coords, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void vao_index_buffer(VAO *vao, unsigned int indices[], int indices_count) {
	glGenBuffers(1, &vao->index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	vao->indices_count = indices_count;
}

void vao_free(VAO *vao) {
	if (vao->vertex_buffer != NULL) {
		glDeleteBuffers(1, &vao->vertex_buffer);
	}
	if (vao->texture_buffer != NULL) {
		glDeleteBuffers(1, &vao->texture_buffer);
	}
	if (vao->index_buffer != NULL) {
		glDeleteBuffers(1, &vao->index_buffer);
	}
	glDeleteVertexArrays(1, &vao->id);
	free(vao);
}

Model *model_load(const char *obj_path, const char *texture_path) {
	Model *m = xmalloc(sizeof(Model));
	FILE *obj_file = fopen(obj_path, "r");
	unsigned int *vertex_indices = NULL;
	unsigned int *uv_indices = NULL;
	unsigned int *normal_indices = NULL;
	Vertex *temp_vertices = NULL;
	Vertex *temp_normals = NULL;
	UV *temp_uvs = NULL;
	Vertex *vertices = NULL;
	Vertex *normals = NULL;
	UV *uvs = NULL;
	int i;

	if (!obj_file) {
		fprintf(stderr, "Could'nt open file %s!\n", obj_path);
		exit(EXIT_FAILURE);
	}

	while (1) {
		char line[128];
	    int res = fscanf(obj_file, "%s", line);
		if (res == EOF) {
			break;
		}
		if (strcmp(line, "v") == 0){
			Vertex vertex;
			int matches = fscanf(obj_file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			if (matches != 3){
				fprintf(stderr, "Failed to parse oject file '%s'!\n", obj_path);
				exit(EXIT_FAILURE);
			}
			sb_push(temp_vertices, vertex);
		} else if (strcmp(line, "vt") == 0){
			UV uv;
			fscanf(obj_file, "%f %f\n", &uv.x, &uv.y);
			sb_push(temp_uvs, uv);
		}else if (strcmp(line, "vn") == 0){
			Vertex normal;
			int matches = fscanf(obj_file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			if (matches != 3){
				fprintf(stderr, "Failed to parse oject file '%s'!\n", obj_path);
				exit(EXIT_FAILURE);
			}
			sb_push(temp_normals, normal);
		}else if (strcmp(line, "f") == 0 ){
			unsigned int vertex_index[3], uv_index[3], normal_index[3];
			int matches = fscanf(obj_file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
			if (matches != 9){
				fprintf(stderr, "Failed to parse oject file '%s'!\n", obj_path);
				exit(EXIT_FAILURE);
			}

			sb_push(vertex_indices, vertex_index[0]);
			sb_push(vertex_indices, vertex_index[1]);
			sb_push(vertex_indices, vertex_index[2]);
			sb_push(uv_indices, uv_index[0]);
			sb_push(uv_indices, uv_index[1]);
			sb_push(uv_indices, uv_index[2]);
			sb_push(normal_indices, normal_index[0]);
			sb_push(normal_indices, normal_index[1]);
			sb_push(normal_indices, normal_index[2]);
		}
	}

	for(i = 0; i < sb_len(vertex_indices); i++) {
		unsigned int vertex_index = vertex_indices[i];
		unsigned int uv_index = uv_indices[i];
		unsigned int normal_index = normal_indices[i];
		
		Vertex vertex = temp_vertices[vertex_index - 1];
		UV uv = temp_uvs[uv_index - 1];
		Vertex normal = temp_normals[normal_index - 1];
		
		sb_push(vertices, vertex);
		sb_push(uvs, uv);
		sb_push(normals, normal);
	}

	m->vao = vao_new();
	m->texture = texture_new(texture_path);
	m->vertices_count = sb_len(vertices);

	vao_bind(m->vao);
	vao_vertex_buffer(m->vao, vertices, sb_len(vertices));
	vao_texture_buffer(m->vao, uvs, sb_len(uvs));

	sb_free(vertex_indices);
	sb_free(uv_indices);
	sb_free(normal_indices);
	sb_free(temp_vertices);
	sb_free(temp_normals);
	sb_free(temp_uvs);
	sb_free(vertices);
	sb_free(uvs);
	sb_free(normals);

	return m;
}

void model_render(Model *m) {
	glActiveTexture(GL_TEXTURE0);
	texture_bind(m->texture);
	vao_bind(m->vao);
	glDrawArrays(GL_TRIANGLES, 0, m->vertices_count);
	vao_unbind(m->vao);
}

void model_free(Model *m) {
	texture_free(m->texture);
	vao_free(m->vao);
}