/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:32 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/17 18:10:57 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

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
	if (keycode == 53)
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
	int		i;

	init_sc(&sc);
	if (argc != 2)
		exit_clean(1, "Bad usage");
	i = ft_strlen(argv[1]);
	if (i < 5)
		return (1);
	if (argv[1][i - 1] != 'f' || argv[1][i - 2] != 'd'
		|| argv[1][i - 3] != 'f' || argv[1][i - 4] != '.')
		return (1);
	parse_map(argv[1], &sc);
	setup_scene(&sc);
	mlx_key_hook(sc.ft.win, hook_key, &sc);
	mlx_hook(sc.ft.win, 17, 0, close_me, &sc);
	mlx_expose_hook(sc.ft.win, render, &sc);
	mlx_loop_hook(sc.ft.mlx, render, &sc);
	mlx_loop(sc.ft.mlx);
	return (0);
}
