#ifndef GLUE_SHAPE_H
#define GLUE_SHAPE_H

#include "vertex.h"
#include "color.h"
#include "texture.h"

#define GLUE_VERT_MIDDLE 1<<0
#define GLUE_VERT_TOP    1<<1
#define GLUE_VERT_BOTTOM 1<<2
#define GLUE_HORI_MIDDLE 1<<3
#define GLUE_HORI_LEFT 1<<4
#define GLUE_HORI_RIGHT 1<<5

struct glue_shape {
	unsigned int pos_x;
	unsigned int pos_y;
	float angle;
	float scale_x;
	float scale_y;
	unsigned int vertex_count;
	struct glue_shape_vertex *vertices;
	struct glue_rgba_n color;
	unsigned int vbo;
	unsigned int vao;
};

#endif
