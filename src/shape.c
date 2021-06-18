#include "shape.h"
#include "vertex.h"

#include <GL/glew.h>

#include <stddef.h>
#include <stdlib.h>

int glue_shape_init(struct glue_shape *shape) {
	glGenBuffers(1, &shape->vbo);
	glGenVertexArrays(1, &shape->vao);
	glBindVertexArray(shape->vao);
	glBindBuffer(GL_ARRAY_BUFFER, shape->vbo);
	glBufferData(GL_ARRAY_BUFFER, 
			sizeof(struct glue_shape_vertex) * 
			shape->vertex_count,
			shape->vertices,
			GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct glue_shape_vertex), (void*)0);
	glEnableVertexAttribArray(0);
	return 0;
}

int glue_shape_ngon(struct glue_shape *shape,
		struct glue_shape_vertex *vertices,
		struct glue_rgba_n color,
		unsigned int vertex_count,
		unsigned int pos_x,
		unsigned int pos_y,
		float angle) {
	shape->pos_x = pos_x;
	shape->pos_y = pos_y;
	shape->angle = angle;
	shape->color = color;
	shape->scale_x = 1;
	shape->scale_y = 1;
	shape->vertex_count = vertex_count;
	shape->vertices = malloc(sizeof(struct glue_shape_vertex)*vertex_count);
	memcpy(shape->vertices, vertices, sizeof(struct glue_shape_vertex) * vertex_count);
	glue_shape_init(shape);
	return 0;
}

int glue_shape_free(struct glue_shape *shape) {
	shape->vertex_count = 0;
	free(shape->vertices);
	shape->vertices = NULL;
	return 0;
}
