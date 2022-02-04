#include <libftmlx/math.h>
#include "fdf.h"

/*
t_mat4 create_orth_cam(float height, float width, float far, float near)
{
	t_mat4 m;
	m = (t_mat4){MAT4_ID};
	m.m[0][0] = 1 / width;
	m.m[1][1] = 1 / height;
	m.m[2][2] = -2 / (far - near);
	m.m[2][3] = -(far + near) / (far - near);
	return m;
}
*/

t_mat4 create_orth_cam(float height, float width, float far, float near, t_transform cam)
{
	t_mat4 mat_persp;
	mat_persp = (t_mat4){MAT4_ID};
	mat_persp.m[0][0] = 2 / width;
	mat_persp.m[1][1] = 2 / height;
	mat_persp.m[2][2] = -2 / (far - near);
	mat_persp.m[2][3] = -(far + near) / (far - near);

	return mult_mat_mat(mat_persp, transform_to_mat(transform_inv(cam)));
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_transform cam = {euler_to_quat((t_euler){0, 0, 0}),
										 {-5, -5, 10}};
	t_mat4 proj = create_orth_cam(10, 10, 10, 0, cam);

	t_vec4 point = (t_vec4){0, 0, 0, 1};
	t_vec4 out = mult_mat_vec(proj, point);

	return 0;
} 