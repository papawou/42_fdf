/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:10:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/17 17:03:43 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

void	exit_clean(int code, char *str)
{
	if (code)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd(str, 1);
	clean_scene(E_CODE_CLEAN, NULL);
	exit(code);
}

void	clean_scene(int code, t_scene *sc)
{
	static t_scene	*p_sc = NULL;

	if (code & E_CODE_INIT)
		p_sc = sc;
	if (code & E_CODE_CLEAN)
	{
		ft_free_malloc_cont_2d((void **)p_sc->map);
		p_sc->map = NULL;
		ft_free_malloc_cont_2d((void **)p_sc->map_color);
		p_sc->map_color = NULL;
		if (p_sc->ft.mlx)
		{
			if (p_sc->canvas)
				ftmlx_free_img(p_sc->ft.mlx, p_sc->canvas);
			p_sc->canvas = NULL;
			if (p_sc->ft.win)
				mlx_destroy_window(p_sc->ft.mlx, p_sc->ft.win);
			p_sc->ft.win = NULL;
			free(p_sc->ft.mlx);
			p_sc->ft.mlx = NULL;
		}
	}
}

void	init_sc(t_scene *sc)
{
	sc->map = NULL;
	sc->map_color = NULL;
	sc->ft.mlx = NULL;
	sc->ft.win = NULL;
	sc->canvas = NULL;
	clean_scene(E_CODE_INIT, sc);
}

t_vec2	get_screen_size(t_fvec2 height, t_fvec2 width, t_scene *sc)
{
	t_fvec2	dst;
	float	scale_map;
	t_fvec2	box;

	box.x = width.y - width.x;
	box.y = height.y - height.x;
	dst.x = 1000;
	dst.y = 1000;
	if (box.x > box.y)
	{
		dst.y = dst.x * (box.y / box.x);
		scale_map = 1000.0 / box.x;
	}
	else
	{
		dst.x = dst.y * (box.x / box.y);
		scale_map = 1000.0 / box.y;
	}
	scale_map *= 0.9;
	sc->map_mat = scale_map_mat(scale_map);
	setup_cam(sc);
	fps_move_camera((t_fvec3){-dst.x * 0.05,
		height.y * scale_map + dst.y * 0.05, 0}, &sc->cam);
	return ((t_vec2){dst.x, dst.y});
}

void	setup_scene(t_scene *sc)
{
	t_vec2	screen_size;
	t_fvec2	tmp_height;
	t_fvec2	tmp_width;

	calc_map_box(&tmp_height, &tmp_width, sc);
	screen_size = get_screen_size(tmp_height, tmp_width, sc);
	if (screen_size.x < 360)
	{
		fps_move_camera((t_fvec3){(-360 - screen_size.x) / 2.0, 0, 0},
			&sc->cam);
		screen_size.x = 360;
	}
	else if (screen_size.y < 360)
	{
		fps_move_camera((t_fvec3){0, (360 - screen_size.y) / 2.0, 0}, &sc->cam);
		screen_size.y = 360;
	}
	if (ftmlx_init(screen_size.x, screen_size.y, &sc->ft))
		exit_clean(1, "ftmlx failed");
	sc->canvas = ftmlx_new_img(sc->ft.mlx, sc->ft.wh.x, sc->ft.wh.y);
	if (sc->canvas == NULL)
		exit_clean(1, "canvas failed");
	ftmlx_get_color_value(sc->ft.mlx, 0);
}
