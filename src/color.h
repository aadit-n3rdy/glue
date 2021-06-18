#ifndef GLUE_COLOR_H
#define GLUE_COLOR_H

struct glue_rgba {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

struct glue_rgba_n {
	float red;
	float green;
	float blue;
	float alpha;
};

struct glue_rgba_n glue_rgba_normalise(struct glue_rgba color);

#endif
