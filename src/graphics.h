typedef struct {
	float x, y, z;
} Vertex;

typedef struct {
	GLuint id;
} Texture;

Texture *texture_new(const char *texture_path);
void texture_bind(Texture *t);
void texture_free(Texture *t);