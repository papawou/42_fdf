/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:10:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/22 03:23:27 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void exit_clean(int code, char *str)
{
	(void) str;
	clean_scene(E_CODE_CLEAN, NULL);
	exit(code);
}

void	clean_scene(int code, t_scene *sc)
{
	static t_scene *p_sc = NULL;

	if (code & E_CODE_INIT)
		p_sc = sc;
	
	if (code & E_CODE_CLEAN)
	{
		ft_free_malloc_cont_2d((void **)p_sc->depth_buffer);
		p_sc->depth_buffer = NULL;
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
		}
	}
}

void	init_sc(t_scene *sc)
{
	sc->map = NULL;
	sc->map_color = NULL;
	sc->depth_buffer = NULL;
	sc->ft.mlx = NULL;
	sc->ft.win = NULL;
	sc->canvas = NULL;
	clean_scene(E_CODE_INIT, sc);
}
