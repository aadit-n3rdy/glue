#include "renderer.h"
#include "color.h"
#include "mosaic.h"

#include <GL/glew.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

int glue_renderer_compile_shape_shader(struct glue_renderer *renderer) {
	int ret = 0;
	char *buffer = malloc(2048);
	size_t len;
	unsigned int vertex_shader, fragment_shader;
	FILE *fp  = fopen("shaders/shape.vert", "r");
	if (fp) {
		len = fread(buffer, sizeof(char), 2048, fp);
		buffer[len] = '\0';
	} else {
		printf("ERROR: Could not open shape vertex shader\n");
		ret = -1;
		goto done;
	}
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &buffer, &len);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		bzero(buffer, 256);
		glGetShaderInfoLog(vertex_shader, 2048, NULL, buffer);
		printf("ERROR <GLEW>: Could not compile shape vertex shader\n%s\n",
				buffer);
		goto done;
	}
	fclose(fp);
	bzero(buffer, 2048);
	fp  = fopen("shaders/shape.frag", "r");
	if (fp) {
		len = fread(buffer, sizeof(char), 2048, fp);
		buffer[len] = '\0';
	} else {
		printf("ERROR: Could not open shape fragment shader\n");
		ret = -1;
		goto done;
	}
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &buffer, &len);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		bzero(buffer, 256);
		glGetShaderInfoLog(fragment_shader, 2048, NULL, buffer);
		printf("ERROR <GLEW>: Could not compile shape fragment shader\n%s\n",
				buffer);
		goto done;
	}
	fclose(fp);
	renderer->shape_shader = glCreateProgram();
	glAttachShader(renderer->shape_shader, vertex_shader);
	glAttachShader(renderer->shape_shader, fragment_shader);
	glLinkProgram(renderer->shape_shader);
	glGetProgramiv(renderer->shape_shader, GL_LINK_STATUS, &ret);
	if (!ret) {
		bzero(buffer, 256);
		glGetProgramInfoLog(renderer->shape_shader, 2048, NULL, buffer);
		printf("ERROR <GLEW>: Could not link shape shader program\n%s\n",
				buffer);
		goto done;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
done:
	free(buffer);
	return ret;
}

int glue_renderer_set_bkg(struct glue_rgba color) {
	struct glue_rgba_n color_n = glue_rgba_normalise(color);
	glClearColor(color_n.red, color_n.green, color_n.blue, color_n.alpha);
	return 0;
}

int glue_renderer_clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 0;
}

int glue_renderer_draw_shape(struct glue_renderer *renderer, struct glue_shape *shape) {
	struct mosaic_matrix rot;
	struct mosaic_matrix scale;
	struct mosaic_matrix rot_scale;
	float scale_raw[] = {shape->scale_x, 0, 0, shape->scale_y};
	float cos_theta = cosf(shape->angle);
	float sin_theta = sinf(shape->angle);
	float rot_raw[] = {cos_theta, sin_theta, -sin_theta, cos_theta};
	float move[] = { (float)shape->pos_x,
		(float)shape->pos_y};
	mosaic_matrix_init(&rot, 2, 2);
	mosaic_matrix_init(&scale, 2, 2);
	mosaic_matrix_init(&rot_scale, 2, 2);
	mosaic_matrix_assign(&rot, rot_raw);
	mosaic_matrix_assign(&scale, scale_raw);
	mosaic_matrix_multiply(&rot, &scale, &rot_scale);
	glUseProgram(renderer->shape_shader);
	int move_uniform = glGetUniformLocation(renderer->shape_shader, "move");
	int rot_scale_uniform = glGetUniformLocation(renderer->shape_shader, "rot_scale");
	glUniform2fv(move_uniform, 1, move);
	glUniformMatrix2fv(rot_scale_uniform, 1, GL_TRUE, rot_scale.raw);
	int width_unif = glGetUniformLocation(renderer->shape_shader, "width");
	int height_unif = glGetUniformLocation(renderer->shape_shader, "height");
	int col_unif = glGetUniformLocation(renderer->shape_shader, "color");
	glUniform1f(width_unif, (float)renderer->window->width);
	glUniform1f(height_unif, (float)renderer->window->height);
	glUniform4fv(col_unif, 1, (float*)&shape->color);
	glBindVertexArray(shape->vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, shape->vertex_count);
	mosaic_free(&rot);
	mosaic_free(&scale);
	mosaic_free(&rot_scale);
	return 0;
}
