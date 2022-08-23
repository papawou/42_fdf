/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:29 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/24 00:57:24 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void draw_debug(t_scene *sc)
{
	t_vec2 a;
	t_vec2 b;
	t_color c[2];
 
	a = (t_vec2) {0, 0};
	b = (t_vec2) {10, 50};
	
	c[0] = (t_color) {255, 0,0,0};
	c[1] = c[0];
	ftmlx_put_bresen_line(a, b, c, sc->canvas);
	c[0] = (t_color) {0, 255, 0, 0};
	c[1] = c[0];
	ftmlx_put_bresen_line(b, a, c, sc->canvas);
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
				ftmlx_put_line(sc->ft3d, a, b, (t_color[2]){(t_color){255, 0, 0, 0}, (t_color){0, 255, 0, 0}});
				ftmlx_put_line(sc->ft3d, a, b, (t_color[2]){(t_color){255, 0, 0, 0}, (t_color){0, 255, 0, 0}});
			}
			if (z < sc->map_size.y - 1)
			{
				b = (t_fvec4){x, sc->map[z + 1][x], z+1, 1};
				ftmlx_put_line(sc->ft3d, a, b, (t_color[2]){(t_color){255, 0, 0, 0}, (t_color){0, 255, 0, 0}});
				ftmlx_put_line(sc->ft3d, a, b, (t_color[2]){(t_color){255, 0, 0, 0}, (t_color){0, 255, 0, 0}});
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
