typedef struct {
	float x, y, z;
} Vertex;

typedef struct {
	float x, y;
} UV;

typedef struct {
	GLuint id;
} Texture;

Texture *texture_new(const char *texture_path);
void texture_bind(Texture *t);
void texture_free(Texture *t);

typedef struct {
	GLuint id;
	GLuint vertex_buffer;
	GLuint texture_buffer;
	GLuint index_buffer;
	int indices_count;
} VAO;

VAO *vao_new();
void vao_bind(VAO *vao);
void vao_unbind(VAO *vao);
void vao_vertex_buffer(VAO *vao, Vertex vertices[], int vertices_count);
void vao_texture_buffer(VAO *vao, UV texture_coords[], int txc_count);
void vao_index_buffer(VAO *vao, unsigned int indices[], int indices_count);
void vao_free(VAO *vao);

typedef struct {
	VAO *vao;
	Texture *texture;
	int vertices_count;
} Model;

Model *model_load(const char *obj_path, const char *texture_path);
void model_render(Model *m);
void model_free(Model *m);