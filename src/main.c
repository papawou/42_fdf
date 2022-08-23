/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:32 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/24 00:57:31 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include <X11/keysym.h>
#include <stdio.h>

#include "fdf.h"

int	close_me(void)
{
	exit_clean(1, "LALAL");
	return (0);
}

int	hook_key(int keycode, t_scene *sc)
{
	controls_camera_listener(keycode, sc);
	if (keycode == XK_Escape)
		close_me();
	return (0);
}

int	render(t_scene *sc)
{
	fill_img(sc->canvas, (t_color){127, 127, 127, 0});
	ft_bzero(sc->depth_buffer[0], sizeof(float) * sc->ft.wh.y * sc->ft.wh.x);


	//draw_debug(sc);
	draw_map_wire(sc);
	//draw_map_triangle(sc);
	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);

	return (0);
}

void	setup_cam(t_scene *sc)
{
	t_transform	tranf;
	t_mat4		proj;

	tranf = (t_transform){euler_to_quat((t_euler){-35.264, 45, 0}),
		(t_fvec3){0, 0, 0}};
	//proj = ftmlx_create_x_persp_proj(60, sc->ft.wh.x / sc->ft.wh.y, 1000, 1);
	proj = ftmlx_create_orth_proj(50, 50, 500, 1);
	ftmlx_init_cam(tranf, proj, (t_fvec3){0, 0, 0}, &sc->cam);
}

void	setup_scene(t_scene *sc)
{
	if (ftmlx_init(1280, 720, &sc->ft))
		exit_clean(1, "LALAL");
	sc->depth_buffer = (float **)ft_malloc_cont_2d(sc->ft.wh.y, sc->ft.wh.x,
			sizeof(float));
	if (sc->depth_buffer == NULL)
		exit_clean(1, "LALAL");
	sc->canvas = ftmlx_new_img(sc->ft.mlx, sc->ft.wh.x, sc->ft.wh.y);
	if (sc->canvas == NULL)
		exit_clean(1, "LALAL");
	setup_cam(sc);
	sc->ft3d = (t_ftmlx3d){&sc->cam.vp, &sc->ft.wh, sc->canvas};
}

int	main(int argc, char *argv[])
{
	t_scene	sc;

	(void)argc;
	(void)argv;
	if (argc < 1)
		return (1);
	init_sc(&sc);
	if (parse_map(argv[1], &sc))
		return (1);
	setup_scene(&sc);
	render(&sc);
	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return (0);
}
