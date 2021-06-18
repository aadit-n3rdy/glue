#ifndef GLUE_WINDOW_H
#define GLUE_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct glue_window {
	GLFWwindow* winptr;
	unsigned int width;
	unsigned int height;
	const char *title;
};

#endif
