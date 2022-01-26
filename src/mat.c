#include "mat.h"

/*
column major
dst <- m * v

opt? t_mat4 to float *m[4][4] => involve calling func(vec, &mat.m)
*/

t_vec4 mult_vec_mat(const t_vec4 v, const t_mat4 m)
{
	t_vec4 dst;

	dst.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	dst.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	dst.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	dst.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return dst;
}