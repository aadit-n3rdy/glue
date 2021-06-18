#ifndef GLUE_RENDERER_H
#define GLUE_RENDERER_H

#include "shape.h"
#include "color.h"
#include "window.h"

struct glue_renderer {
	unsigned int shape_shader;
	struct glue_window *window;
};

int glue_renderer_compile_shape_shader();

int glue_renderer_draw_shape(struct glue_renderer *renderer, struct glue_shape *shape);

#endif
