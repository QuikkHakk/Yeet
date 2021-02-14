#include <stdio.h>

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		fprintf(stderr, "Failed to load texture file %s!\n", texture_path);
		exit(EXIT_FAILURE);
	}

	stbi_image_free(data);

	return t;
}

void texture_bind(Texture *t) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, t->id);
}

void texture_free(Texture *t) {
	glDeleteTextures(1, &t->id);
	free(t);
}