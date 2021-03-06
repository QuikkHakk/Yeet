#include <stdio.h>
#include <stdlib.h>

#include <cglm/cglm.h>
#include <GL/glew.h>

#include "shader.h"
#include "utils.h"

static GLuint shader_create_compile(GLenum shader_type, char *src);

Shader *shader_new(const char *vertex_path, const char *fragment_path) {
	Shader *s = xmalloc(sizeof(Shader));
	GLuint vertex_shader, fragment_shader;
	char *vertex_source;
	char *fragment_source;
	
	vertex_source = read_file(vertex_path);
	fragment_source = read_file(fragment_path);
		
	vertex_shader = shader_create_compile(GL_VERTEX_SHADER, vertex_source);
	fragment_shader = shader_create_compile(GL_FRAGMENT_SHADER, fragment_source);
	s->id = glCreateProgram();
	glAttachShader(s->id, vertex_shader);
	glAttachShader(s->id, fragment_shader);
	glLinkProgram(s->id);
  
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	free(vertex_source);
	free(fragment_source);

	return s;
}

void shader_enable(Shader *s) {
	glUseProgram(s->id);
}

void shader_disable(Shader *s) {
	glUseProgram(0);
}

void shader_load_float(Shader *s, const char *uniform_name, float v) {
	GLuint location = glGetUniformLocation(s->id, uniform_name);
	glUniform1f(location, v);
}

void shader_load_vec3(Shader *s, const char *uniform_name, vec3 vec) {
	GLuint location = glGetUniformLocation(s->id, uniform_name);
	glUniform3fv(location, 1, vec);
}

void shader_load_vec4(Shader *s, const char *uniform_name, vec4 vec) {
	GLuint location = glGetUniformLocation(s->id, uniform_name);
	glUniform4fv(location, 1, vec);
}

void shader_load_mat4(Shader *s, const char *uniform_name, mat4 mat) {
	GLuint location = glGetUniformLocation(s->id, uniform_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, (float *)mat);
}

void shader_free(Shader *s) {
	glDeleteProgram(s->id);
	free(s);
}

static GLuint shader_create_compile(GLenum shader_type, char *src) {
	GLuint shader = glCreateShader(shader_type);
	int success;
	char info[512];

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, info);
		printf("%s compilation error.\n", shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
		puts(info);
		exit(EXIT_FAILURE);
	};
	return shader;
}