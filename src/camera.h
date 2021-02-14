typedef struct {
	vec3 position;
	mat4 view_matrix;
} Camera;

Camera *camera_new(Window *w);
void camera_update(Camera *c, Window *w, float delta);