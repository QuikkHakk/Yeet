typedef struct {
	GLuint id;
	GLuint vertex_buffer;
} VAO;

VAO *vao_new();
void vao_bind(VAO *vao);
void vao_unbind(VAO *vao);
void vao_vertex_buffer(VAO *vao, Vertex vertices[], int vertices_count);
void vao_free(VAO *vao);