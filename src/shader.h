typedef struct {
	GLuint id;
} Shader;

Shader *shader_new(const char *vertex_path, const char *fragment_path);
void shader_enable(Shader *s);
void shader_disable(Shader *s);
void shader_free(Shader *s);