typedef struct {
	mat4 view_matrix;
	vec3 position;
	vec3 target;
} Camera;

Camera *camera_new();
void camera_update(Camera *c);