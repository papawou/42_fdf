#include <X11/keysym.h>
#include <fcntl.h>
#include "fdf.h"

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

int close_me(t_scene *sc)
{
	// mlx_destroy_window?
	ftmlx_free_img(sc->ft.mlx, sc->canvas);
	exit(0);
	return 0;
}

int render(t_scene *sc)
{
	fill_img(sc->canvas, (t_color){0, 0, 0, 255});
	draw_map_triangle(sc);

	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);
	return 0;
}

void setup_cam(t_scene *sc)
{
	t_transform tranf;
	t_mat4 proj;
	float scale;

	tranf = (t_transform){euler_to_quat((t_euler){0, 0, 0}), (t_fvec3){0, 0, 200}};
	scale = 0.05;
	proj = ftmlx_create_orth_proj(sc->ft.wh.x * scale, sc->ft.wh.y * scale, 1000, 0);
	// t_mat4 proj = ftmlx_create_x_persp_proj(90.0, sc->ft.wh.x / sc->ft.wh.y, 1.0, 1000);
	ftmlx_init_cam(tranf, proj, (t_fvec3){0, 0, 0}, &sc->cam);
}

int parse_map(char *map_path, t_scene *sc)
{
	char *line;
	int fd_map;
	int i;
	// sc->tr_map.q = (t_quat)QUAT_ID;
	// sc->tr_map.v = (t_fvec3){0, 0, 0};

	fd_map = open(map_path, O_RDONLY);
	line = get_next_line(fd_map);
	sc->map_size.x = ft_strlen(line);
	i = 0;
	while (line)
	{
		free(line);
		get_next_line(fd_map);
		++i;
	}
	sc->map_size.y = i;
	sc->map = malloc(sizeof(int *) * sc->map_size.y);
	line = get_next_line(fd_map); // reopen?
	i = 0;
	while (line)
	{
		sc->map[i] = malloc(sc->map_size.x * sizeof(int));
		while (atoi())
		{
			
		}

		++i;
		line = get_next_line(fd_map);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_scene sc;
	t_char map[];

	ftmlx_init(700, 700, &sc.ft);
	setup_cam(&sc);
	sc.canvas = ftmlx_new_img(sc.ft.mlx, sc.ft.wh.x, sc.ft.wh.y);
	sc.ft3d = (t_ftmlx3d){&sc.cam.vp, &sc.ft.wh, sc.canvas};
	map = parse_map(argv[1], &sc);
	render(&sc);

	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return 0;
}