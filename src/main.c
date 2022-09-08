/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:32 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/08 20:02:01 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include <X11/keysym.h>
#include <stdio.h>

#include "fdf.h"

int	close_me(t_scene *sc)
{
	(void) sc;
	clean_scene(E_CODE_CLEAN, NULL);
	exit(0);
	return (0);
}

int	hook_key(int keycode, t_scene *sc)
{
	controls_camera_listener(keycode, sc);
	if (keycode == XK_Escape)
		close_me(sc);
	return (0);
}

int	render(t_scene *sc)
{
	if (sc->ft.win == NULL)
		return (0);
	fill_img(sc->canvas, (t_color){0, 0, 0, 0});
	ftmlx_update_cam(&sc->cam);
	draw(sc);
	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene	sc;

	init_sc(&sc);
	if (argc != 2)
		exit_clean(1, "Bad usage");
	parse_map(argv[1], &sc);
	setup_scene(&sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return (0);
}
