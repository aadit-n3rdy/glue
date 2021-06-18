#include "input.h"
#include "window.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

int glue_get_keystate(struct glue_window *window, int key) {
	return glfwGetKey(window->winptr, key);
}
