#include "window.h"
#include "renderer.h"
#include "color.h"
#include "vertex.h"
#include "shape.h"
#include "input.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <stdlib.h>

int main(void)
{
	struct glue_window window;
	glue_init();
	glue_window_init(&window, 640, 480, "Hello World", 1);
	
	struct glue_shape shape;
	struct glue_rgba color_fg = {0, 255, 255, 255};
	struct glue_rgba_n color_fg_n = {0, 1, 1, 1};

	struct glue_shape_vertex *vertice = malloc(sizeof(struct glue_shape_vertex) * 4);

	vertice[0].pos_x = 0;
	vertice[0].pos_y = 0;

	vertice[1].pos_x = 50;
	vertice[1].pos_y = 0;

	vertice[2].pos_x = 50;
	vertice[2].pos_y = 50;

	vertice[3].pos_x = 0;
	vertice[3].pos_y = 50;

	glue_shape_ngon(&shape, vertice, color_fg_n, 4, 320, 240, 0);

	struct glue_renderer renderer;
	if (!glue_renderer_compile_shape_shader(&renderer)) {
		exit(0);
	}
	renderer.window = &window;
	struct glue_rgba color = {0, 0, 0, 255};
	glue_renderer_set_bkg(color);

	float step = 0.05;
	float scale_step = 0.05;

	while (!glfwWindowShouldClose(window.winptr) && 
			glue_get_keystate(&window, GLUE_KEY_ESCAPE)!= GLUE_PRESSED) {
		glue_renderer_clear();

		if (shape.angle >= 6.28) {
			shape.angle = 0;
		}
		shape.angle += step; 

		if (shape.scale_x > 3) {
			scale_step = -0.05;
		} else if (shape.scale_x < 1) {
			scale_step = 0.05;
		}
		shape.scale_x += scale_step;

		glue_renderer_draw_shape(&renderer, &shape);

		glue_window_update(&window);

	}
	glue_shape_free(&shape);
	glue_terminate();
	return 0;
}
