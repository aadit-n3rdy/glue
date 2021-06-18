#include "color.h"

struct glue_rgba_n glue_rgba_normalise(struct glue_rgba color) {
	struct glue_rgba_n normalised;
	normalised.red = (float)color.red/(float)255;
	normalised.green = (float)color.green/(float)255;
	normalised.blue  = (float)color.blue/(float)255;
	normalised.alpha = (float)color.alpha/(float)255;
	return normalised;
}
