#include <libftmlx.h>

t_fvec3 tri_point_bar(t_vec2 a, t_vec2 b, t_vec2 c, t_vec2 point)
{
	t_fvec3 w;

	float tri_a = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
	w.x = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y)) / tri_a;
	w.y = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y)) / tri_a;
	w.z = 1 - w.x - w.y;
	return w;
}

float barerp(float a, float b, float c, t_fvec3 w)
{
	return w.x * a + w.y * b + w.z * c;
}

t_color color_barerp(t_color a, t_color b, t_color c, t_fvec3 w)
{
	t_color dst;

	dst.r = barerp(a.r, b.r, c.r, w);
	dst.g = barerp(a.g, b.g, c.g, w);
	dst.b = barerp(a.b, b.b, c.b, w);
	dst.a = barerp(a.a, b.a, c.a, w);
	return dst;
}

float fvec3_dot(t_fvec3 a, t_fvec3 b)
{
	float dot;
	float magn_a = fvec3_magn(a);
	float magn_b = fvec3_magn(b);

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot / magn_a) / magn_b;
}

t_fvec3	fvec3_cross(t_fvec3 a, t_fvec3 b)
{
	/*
		axb
		|   b
		|	 /
		| /
		0----a
	*/
	t_fvec3 cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return cross;
}