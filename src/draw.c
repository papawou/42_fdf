/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:29 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/03 03:29:54 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void draw_debug(t_scene *sc)
{
	int x;
	int z;
	t_fvec4 a;
	t_fvec4 dst;
	t_mat4	mvp_map;

	x = 0;
	z = 0;
	
	mvp_map = mat_mult(sc->cam.vp, sc->map_mat);
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			a = (t_fvec4){x, sc->map[z][x], z, 1};
			//ftmlx_put_vertex(sc->ft3d, a, (t_color){255, 0, 0, 0});
			dst = mat_mult_vec(mvp_map, a);
			dst.y = -dst.y;
			printf("%.2f %.2f %.2f \n", dst.x, -dst.y, dst.z);
			ftmlx_img_set_pxl_color(sc->canvas, dst.x, dst.y,
				ftmlx_get_color_int((t_color){255, 0, 0, 0}));
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
				b = (t_fvec4){x, sc->map[z + 1][x], z+1, 1};
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
