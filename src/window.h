typedef struct {
	GLFWwindow *handle;
	const char *title;
	GLint width, height;
} Window;

Window *window_new(const char *title, GLint width, GLint height);
int window_should_close(Window *win);
void window_update_pre(Window *win);
void window_update_post(Window *win);
void window_close(Window *win);