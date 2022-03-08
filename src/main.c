#include <X11/keysym.h>
#include "fdf.h"

int hook_key(int keycode, t_scene *sc)
{
	t_ftcam *cam = &sc->cam;
	if (keycode == XK_Left)
	{
		cam->tranf = quat_mult_transform((t_quat)euler_to_quat((t_euler){0, -1, 0}), cam->tranf);
	}
	else if (keycode == XK_Right)
	{
		cam->tranf = quat_mult_transform((t_quat)euler_to_quat((t_euler){0, 1, 0}), cam->tranf);
	}
	else if (keycode == XK_Up)
	{
		t_fvec3 x_dir = quat_mult_vec(sc->cam.tranf.q, (t_fvec3){1, 0, 0}); // return direction of x axis after rotation
		t_quat rot = axisg_to_quat((t_axisg){x_dir.x, x_dir.y, x_dir.z, -1});
		cam->tranf = quat_mult_transform(rot, cam->tranf);
	}
	else if (keycode == XK_Down)
	{
		t_fvec3 x_dir = quat_mult_vec(sc->cam.tranf.q, (t_fvec3){1, 0, 0}); // return direction of x axis after rotation
		t_quat rot = axisg_to_quat((t_axisg){x_dir.x, x_dir.y, x_dir.z, 1});
		cam->tranf = quat_mult_transform(rot, cam->tranf);
	}
	ftmlx_update_cam(&sc->cam);
	return 0;
}

int close_me(t_scene *sc)
{
	ftmlx_free_img(sc->ft.mlx, sc->canvas);
	exit(0);
	return 0;
}

int render(t_scene *sc)
{
	fill_img(sc->canvas, (t_color){0, 0, 0, 255});
	draw_map_triangle(sc);
	draw_map_wire(sc);
	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);
	return 0;
}

void setup_cam(t_scene *sc)
{
	t_transform tranf = (t_transform){euler_to_quat((t_euler){0, 0, 0}), (t_fvec3){0, 0, 200}};
	float scale = 0.05;
	t_mat4 proj = ftmlx_create_orth_proj(sc->ft.wh.x * scale, sc->ft.wh.y * scale, 1000, 0);
	// t_mat4 proj = ftmlx_create_x_persp_proj(90.0, sc->ft.wh.x / sc->ft.wh.y, 1.0, 1000);
	ftmlx_init_cam(tranf, proj, (t_fvec3){0, 0, 0}, &sc->cam);
}

int parse_map(t_scene *sc)
{
	sc->map_size.y = 8;
	sc->map_size.x = 3;

	sc->tr_map.q = (t_quat)QUAT_ID;
	sc->tr_map.v = (t_fvec3){0, 0, 0};
	sc->map = (int **)ft_malloc_cont_2d(sc->map_size.y, sc->map_size.x, sizeof(int));

	sc->map[0][0] = -1;
	sc->map[0][1] = 1;
	sc->map[0][2] = 0;
	sc->map[1][0] = 1;
	sc->map[1][1] = 0;
	sc->map[1][2] = -1;
	sc->map[2][0] = 0;
	sc->map[2][1] = -1;
	sc->map[2][2] = 0;
	sc->map[3][0] = 3;
	sc->map[3][1] = 1;
	sc->map[3][2] = 2;
	sc->map[4][0] = 0;
	sc->map[4][1] = 4;
	sc->map[4][2] = 1;
	sc->map[5][0] = 1;
	sc->map[5][1] = 2;
	sc->map[5][2] = 0;
	sc->map[6][0] = 0;
	sc->map[6][1] = 0;
	sc->map[6][2] = 0;
	sc->map[7][0] = 0;
	sc->map[7][1] = 0;
	sc->map[7][2] = 0;

	return 0;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_scene sc;

	ftmlx_init(700, 700, &sc.ft);
	setup_cam(&sc);
	sc.canvas = ftmlx_new_img(sc.ft.mlx, sc.ft.wh.x, sc.ft.wh.y);

	sc.ft3d = (t_ftmlx3d){&sc.cam.vp, &sc.ft.wh, sc.canvas};

	parse_map(&sc);
	render(&sc);
	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return 0;
}