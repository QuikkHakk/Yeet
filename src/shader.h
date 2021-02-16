typedef struct {
	GLuint id;
} Shader;

Shader *shader_new(const char *vertex_path, const char *fragment_path);
void shader_enable(Shader *s);
void shader_disable(Shader *s);
void shader_load_float(Shader *s, const char *uniform_name, float v);
void shader_load_vec3(Shader *s, const char *uniform_name, vec3 vec);
void shader_load_vec4(Shader *s, const char *uniform_name, vec4 vec);
void shader_load_mat4(Shader *s, const char *uniform_name, mat4 mat);
void shader_free(Shader *s);