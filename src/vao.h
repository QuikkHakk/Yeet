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
void vao_texture_buffer(VAO *vao, float texture_coords[], int txc_count);
void vao_index_buffer(VAO *vao, unsigned int indices[], int indices_count);
void vao_free(VAO *vao);