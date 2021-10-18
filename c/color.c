#include "color.h"

void write_color(FILE *f, const vec3_t *color) {
	vec3_t out;
	vec3_mul(&out, color, 255.999);
	fprintf(f, "%i %i %i\n", (int)out.x, (int)out.y, (int)out.z);
}

void calc_ray_color(vec3_t *color, const ray_t *ray, const shapes_t *shapes) {
	rayHit_t hit;

	if (shapes_hit(shapes, ray, 0, HUGE_VAL, &hit)) {
		vec3_t ray_color = { .x = 1, .y = 1, .z = 1 };
		vec3_add(&ray_color, &ray_color, &hit.normal);
		vec3_mul(color, &ray_color, 0.5);
		return;
	}

	vec3_t unit_dir;
	vec3_normalize(&unit_dir, &ray->direction);

	double t = 0.5 * (unit_dir.y + 1.0);

	vec3_t a = { .x = 1.0, .y = 1.0, .z = 1.0 };
	vec3_mul(&a, &a, (1.0 - t));

	vec3_t b = { .x = 0.5, .y = 0.7, .z = 1.0 };
	vec3_mul(&b, &b, t);

	vec3_add(color, &a, &b);
}
