#include <X11/keysym.h>
#include <fcntl.h>
#include "fdf.h"

void draw_debug(t_scene *sc)
{
	t_fvec3 a, b, c;

	a = (t_fvec3){-5, -5, 85};
	b = (t_fvec3){5, -5, 85};
	c = (t_fvec3){0, 0, 0};
	shader_map(a, b, c, sc);
	return;
}

int close_me(t_scene *sc)
{
	// mlx_destroy_window?
	free(sc->depth_buffer[0]);
	free(sc->depth_buffer);
	free_map(sc->map, sc->map_size.y);
	ftmlx_free_img(sc->ft.mlx, sc->canvas);
	exit(0);
	return 0;
}

int hook_key(int keycode, t_scene *sc)
{
	t_fvec3 x_dir; // tothink cam_rot(int direction) -avoid dependance of mlx

	if (keycode == XK_Left)
		rotate_camera((t_quat)euler_to_quat((t_euler){0, -1, 0}), &sc->cam);
	else if (keycode == XK_Right)
		rotate_camera((t_quat)euler_to_quat((t_euler){0, 1, 0}), &sc->cam);
	else if (keycode == XK_Up)
	{
		x_dir = quat_mult_vec(sc->cam.tranf.q, (t_fvec3){1, 0, 0});
		rotate_camera(axisg_to_quat((t_axisg){x_dir.x, x_dir.y, x_dir.z, -1}), &sc->cam);
	}
	else if (keycode == XK_Down)
	{
		x_dir = quat_mult_vec(sc->cam.tranf.q, (t_fvec3){1, 0, 0});
		rotate_camera(axisg_to_quat((t_axisg){x_dir.x, x_dir.y, x_dir.z, 1}), &sc->cam);
	}
	else if (keycode == XK_Escape)
		return close_me(sc);
	ftmlx_update_cam(&sc->cam);
	return 0;
}

int render(t_scene *sc)
{
	fill_img(sc->canvas, (t_color){0, 0, 0, 255});
	ft_bzero(sc->depth_buffer[0], sizeof(float) * sc->ft.wh.y * sc->ft.wh.x);
	draw_map_triangle(sc);
	//  draw_map_wire(sc);
	// draw_debug(sc);
	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);
	return 0;
}

void setup_cam(t_scene *sc)
{
	t_transform tranf;
	t_mat4 proj;
	float scale;

	// tranf = (t_transform){euler_to_quat((t_euler){0, 0, 0}), (t_fvec3){0, 0, 200}};
	// scale = 0.05;
	//  tranf = quat_mult_transform(euler_to_quat((t_euler){0, 0, 0}), tranf);
	//  tranf = (t_transform){euler_to_quat((t_euler){0, 0, 0}), (t_fvec3){0, 0, 200}};
	// proj = ftmlx_create_orth_proj(sc->ft.wh.x * scale, sc->ft.wh.y * scale, 1000, 10);

	tranf = (t_transform){euler_to_quat((t_euler){0, 0, 0}), (t_fvec3){0, 0, 25.0}};
	proj = ftmlx_create_x_persp_proj(90.0, (float)sc->ft.wh.x / sc->ft.wh.y, 30.0, 10.0);

	ftmlx_init_cam(tranf, proj, (t_fvec3){0, 0, 0}, &sc->cam);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_scene sc;

	if (argc < 1)
		return 0;
	if (ftmlx_init(500, 500, &sc.ft))
		return 0;
	setup_cam(&sc);
	sc.depth_buffer = (float **)ft_malloc_cont_2d(sc.ft.wh.y, sc.ft.wh.x, sizeof(float));
	sc.canvas = ftmlx_new_img(sc.ft.mlx, sc.ft.wh.x, sc.ft.wh.y);
	sc.ft3d = (t_ftmlx3d){&sc.cam.vp, &sc.ft.wh, sc.canvas};
	if (parse_map(argv[1], &sc))
		return 0;
	render(&sc);
	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return 0;
}