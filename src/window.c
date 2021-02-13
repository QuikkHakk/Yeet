#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"
#include "window.h"

Window *window_new(const char *title, GLint width, GLint height) {
  Window *win = xmalloc(sizeof(Window));
   GLFWwindow *handle;

  win->width = width;
  win->height = height;
  win->title = title;

  if (!glfwInit()) {
    puts("Could'nt initialize glfw!");
    free(win);
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  handle = glfwCreateWindow(width, height, title, NULL, NULL);
  win->handle = handle;

  if (handle == NULL) {
    puts("Could'nt create window!");
    glfwTerminate();
    free(win);
    return NULL;
  }

  glfwMakeContextCurrent(handle);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    puts("Could'nt initialize glew!");
    return NULL;
  }
  return win;
}

int window_should_close(Window *win) {
    return glfwWindowShouldClose(win->handle);
}

void window_update_pre(Window *win) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void window_update_post(Window *win) {
    glfwSwapBuffers(win->handle);
}

void window_close(Window *win) {
    glfwTerminate();
    free(win);
}