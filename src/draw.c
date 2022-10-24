/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:29 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/14 06:30:44 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

static void	draw_2(t_mat4 mvp_map, int x, int z, t_scene *sc)
{
	t_fvec4	a;
	t_fvec4	b;

	a = mat_mult_vec(mvp_map, (t_fvec4){x, sc->map[z][x], z, 1});
	if (x < sc->map_size.x - 1)
	{
		b = mat_mult_vec(mvp_map,
				(t_fvec4){x + 1, sc->map[z][x + 1], z, 1});
		ftmlx_put_bresen_line((t_vec2){a.x, -a.y}, (t_vec2){b.x, -b.y},
			(t_color[2]){sc->map_color[z][x], sc->map_color[z][x + 1]},
			sc->canvas);
	}
	if (z < sc->map_size.y - 1)
	{
		b = mat_mult_vec(mvp_map,
				(t_fvec4){x, sc->map[z + 1][x], z + 1, 1});
		ftmlx_put_bresen_line((t_vec2){a.x, -a.y}, (t_vec2){b.x, -b.y},
			(t_color[2]){sc->map_color[z][x], sc->map_color[z + 1][x]},
			sc->canvas);
	}
}

void	draw(t_scene *sc)
{
	int		x;
	int		z;
	t_mat4	mvp_map;

	x = 0;
	z = 0;
	mvp_map = mat_mult(sc->cam.vp, sc->map_mat);
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			draw_2(mvp_map, x, z, sc);
			++x;
		}
		++z;
	}
}
