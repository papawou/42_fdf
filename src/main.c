/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:32 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/22 03:43:01 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include <X11/keysym.h>
#include <stdio.h>

#include "fdf.h"


void	draw_debug(t_scene *sc)
{
	t_fvec3	t[3];

	t[0] = (t_fvec3){-5, -5, 85};
	t[1] = (t_fvec3){5, -5, 85};
	t[2] = (t_fvec3){0, 0, 0};
	shader_map(t[0], t[1], t[2], sc);
	return ;
}

int	close_me(t_scene *sc)
{
	free(sc->depth_buffer[0]);
	free(sc->depth_buffer);
	free_map(sc->map, sc->map_size.y);
	ftmlx_free_img(sc->ft.mlx, sc->canvas);
	exit(0);
	return (0);
}

int	hook_key(int keycode, t_scene *sc)
{
	controls_camera_listener(keycode, sc);
	if (keycode == XK_Escape)
		return (close_me(sc));
	return (0);
}

int	render(t_scene *sc)
{
	fill_img(sc->canvas, (t_color){127, 127, 127, 0});
	ft_bzero(sc->depth_buffer[0], sizeof(float) * sc->ft.wh.y * sc->ft.wh.x);
	draw_map_triangle(sc);
	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);
	
	char output[255];
	sprintf(output, "%f / %f / %f", sc->cam.tranf.v.x, sc->cam.tranf.v.y, sc->cam.tranf.v.z);
	mlx_string_put(sc->ft.mlx, sc->ft.win, 50, 50, ftmlx_get_color_int((t_color){255, 0, 0, 0}), output);
	return (0);
}

void	setup_cam(t_scene *sc)
{
	t_transform	tranf;
	t_mat4		proj;

	tranf = (t_transform){euler_to_quat((t_euler){0, 0, 0}),
		(t_fvec3){0, 0, 0}};
	
	/*
	float		scale = 0.25;
	proj = ftmlx_create_orth_proj(sc->ft.wh.x * scale, sc->ft.wh.y * scale,
			1000, 10);
	*/
	proj = ftmlx_create_x_persp_proj(120, sc->ft.wh.x/sc->ft.wh.y, 1000, 1);
	ftmlx_init_cam(tranf, proj, (t_fvec3){0, 0, 0}, &sc->cam);
}

int	main(int argc, char *argv[])
{
	t_scene	sc;

	(void)argc;
	(void)argv;
	if (argc < 1)
		return (0);
	if (ftmlx_init(1280, 720, &sc.ft))
		return (0);
	setup_cam(&sc);
	sc.depth_buffer = (float **)ft_malloc_cont_2d(sc.ft.wh.y, sc.ft.wh.x,
			sizeof(float));
	sc.canvas = ftmlx_new_img(sc.ft.mlx, sc.ft.wh.x, sc.ft.wh.y);
	sc.ft3d = (t_ftmlx3d){&sc.cam.vp, &sc.ft.wh, sc.canvas};
	if (parse_map(argv[1], &sc))
		return (0);
	render(&sc);
	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return (0);
}
