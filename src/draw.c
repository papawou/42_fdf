/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:29 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/03 04:07:32 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void draw_debug(t_scene *sc)
{
	int x;
	int z;
	t_fvec4 a;
	t_fvec4 b;
	t_mat4 mvp_map;

	x = 0;
	z = 0;
	mvp_map = mat_mult(sc->cam.vp, sc->map_mat);
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			// ftmlx_put_vertex(sc->ft3d, a, (t_color){255, 0, 0, 0});
			a = mat_mult_vec(mvp_map, (t_fvec4){x, sc->map[z][x], z, 1});
			//printf("%.2f %.2f %.2f \n", a.x, -a.y, a.z);
			if (x < sc->map_size.x - 1)
			{
				b = mat_mult_vec(mvp_map, (t_fvec4){x + 1, sc->map[z][x + 1], z, 1});
				ftmlx_put_bresen_line((t_vec2){a.x, -a.y}, (t_vec2){b.x, -b.y},
					(t_color[2]){sc->map_color[z][x], sc->map_color[z][x + 1]},
					 sc->canvas);
			}
			if (z < sc->map_size.y - 1)
			{
				b = mat_mult_vec(mvp_map, (t_fvec4){x, sc->map[z + 1][x], z + 1, 1});
				ftmlx_put_bresen_line((t_vec2){a.x, -a.y}, (t_vec2){b.x, -b.y},
					(t_color[2]){sc->map_color[z][x], sc->map_color[z + 1][x]},
					sc->canvas);
			}
			++x;
		}
		++z;
	}
}

void draw_map_wire(t_scene *sc)
{
	int x;
	int z;
	t_fvec4 a;
	t_fvec4 b;

	x = 0;
	z = 0;
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			a = (t_fvec4){x, sc->map[z][x], z, 1};
			if (x < sc->map_size.x - 1)
			{
				b = (t_fvec4){x + 1, sc->map[z][x + 1], z, 1};
				ftmlx_put_line(sc->ft3d, a, b,
											 (t_color[2]){sc->map_color[z][x], sc->map_color[z][x + 1]});
			}
			if (z < sc->map_size.y - 1)
			{
				b = (t_fvec4){x, sc->map[z + 1][x], z + 1, 1};
				ftmlx_put_line(sc->ft3d, a, b,
											 (t_color[2]){sc->map_color[z][x], sc->map_color[z + 1][x]});
			}
			++x;
		}
		++z;
	}
}

void draw_map_triangle(t_scene *sc)
{
	t_fvec3 t[3];
	int **map;
	int x;
	int z;

	x = 0;
	z = 0;
	map = sc->map;
	while (z < sc->map_size.y - 1)
	{
		x = 0;
		while (x < sc->map_size.x - 1)
		{
			t[0] = (t_fvec3){x, map[z][x], z};
			t[1] = (t_fvec3){x, map[z + 1][x], z + 1};
			t[2] = (t_fvec3){x + 1, map[z][x + 1], z};
			shader_map(t[0], t[1], t[2], sc);
			t[0] = (t_fvec3){x + 1, map[z + 1][x + 1], z + 1};
			shader_map(t[2], t[1], t[0], sc);
			++x;
		}
		++z;
	}
}
