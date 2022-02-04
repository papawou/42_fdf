#include "fdf.h"

t_mat4 create_orth_cam(float width, float height, float far, float near, t_transform cam)
{
	t_mat4 mat_persp;
	mat_persp = (t_mat4){MAT4_ID};
	mat_persp.m[0][0] = 2 / width;
	mat_persp.m[1][1] = 2 / height;
	mat_persp.m[2][2] = -2 / (far - near);
	mat_persp.m[2][3] = -(far + near) / (far - near);

	return mult_mat_mat(mat_persp, transform_to_mat(transform_inv(cam)));
}

int render(t_scene *sc)
{
	// projection view
	t_transform cam = {euler_to_quat((t_euler){0, 0, 0}),
										 {-150, -100, 50}};
	t_mat4 proj = create_orth_cam(300, 200, 100, 0, cam);

	int map[2][3] = {{0, 1, 2}, {3, 4, 5}}; //[z][x]
	t_transform tranf_map = {QUAT_ID, {0, 0, 0}};

	int x = 0;
	int z = 0;
	while (z < 2)
	{
		x = 0;
		while (x < 3)
		{
			t_vec4 out_point = mult_mat_vec(proj, (t_vec4){x, map[z][x], z, 1});
			
			++x;
		}
		++z;
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_scene sc;

	sc.mlx = mlx_init();
	sc.win = mlx_new_window(sc.mlx, 300, 200, "fdf");
	sc.canvas = ftmlx_new_img(sc.mlx, 300, 200);

	mlx_loop_hook(sc.mlx, &render, &sc);
	mlx_loop(sc.mlx);
	return 0;
}