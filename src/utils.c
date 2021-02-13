#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "utils.h"

void *xmalloc(size_t size) {
	void *p = malloc(size);
	if (p == NULL) {
		printf("Failed to allocate memory of size %zu\n", size);
		exit(EXIT_FAILURE);
	}
	return p;
}

char *read_file(const char *fname) {
	char *buffer = 0;
	long length;
	FILE *f = fopen(fname, "rb");

	if (f) {
	  fseek (f, 0, SEEK_END);
	  length = ftell(f);
	  fseek(f, 0, SEEK_SET);
	  buffer = xmalloc(length + sizeof(char));
	  if (buffer) {
		fread(buffer, 1, length, f);
		buffer[length] = '\0';
	  }
	  fclose(f);
	} else {
		fprintf(stderr, "Could'nt open file %s!\n", fname);
		exit(EXIT_FAILURE);
	}

	return buffer;
}