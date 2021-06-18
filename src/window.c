#include "window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <stdio.h>

int glue_init() {
	int ret = 0;
	ret = glfwInit();
	return ret;
}

void glue_error_callback(int error, const char *description) {
	printf("ERROR <GLFW>: %s\n", description);
}

void glue_terminate() {
	glfwTerminate();
}

void MessageCallback( GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam )
{
	printf( "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
			type, severity, message );
}


int glue_window_init(struct glue_window *window,
		unsigned int width,
		unsigned int height,
		const char *title,
		char vsync) {
	int ret = 0;
	window->winptr = glfwCreateWindow(width, height, title, NULL, NULL);
	window->width = width;
	window->height = height;
	window->title = title;

	if (window->winptr == NULL) {
		ret = -1;
		glue_terminate();
		goto done;
	}
	glfwMakeContextCurrent(window->winptr);
	glfwSetErrorCallback(glue_error_callback);
	glfwSwapInterval(1);
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		printf("ERROR <GLEW>: %s\n", glewGetErrorString(err));
		ret = -1;
		glue_terminate();
		goto done;
	}
	glewExperimental = GL_TRUE;
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback,0);
	if (vsync) {
		glfwSwapInterval(1);
	}
done:
	return ret;
}

int glue_window_update(struct glue_window *window) {
	glfwSwapBuffers(window->winptr);
	glfwPollEvents();
}

