typedef struct {
	VAO *vao;
	Shader *shader;
} Terrain;

Terrain *terrain_generated();
void terrain_render(Terrain *t, mat4 proj_mat, mat4 view_mat);
void terrain_free(Terrain *t);