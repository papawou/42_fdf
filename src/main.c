#include <libft/math.h>
#include "fdf.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_vec4 out_point;
	(void)out_point;

	t_vec4 point = {0, 0, 0, 1};

	t_quat q = euler_to_quat((t_euler){0, 0, deg_to_rad(90)});
	t_mat4 rot = quat_to_mat(q);
	rot.m[0][3] = 5;
	rot.m[1][3] = 0;
	rot.m[2][3] = 0;
	/*
	t_mat4 mat = {MAT4_ID};
	t_mat4 mat2 = {MAT4_ID};
	mat2.m[0][3] = 0;
	mat2.m[1][3] = 0;
	mat2.m[2][3] = 0;
	mat2 = quat_to_mat(q);
	t_mat4 mat_final = mult_mat_mat(mat2, mat);
	out_point = ft_mult_mat_vec(mat_final, point);
	*/
	out_point = ft_mult_mat_vec(rot, point);

	return 0;
}

/*
	//mat
	//mat to quat
	//transpose mat
	//inverse mat
*/

