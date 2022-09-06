/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:33:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/06 14:29:08 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void calc_map_box_2(t_fvec4 minmax, t_fvec2 *box, t_fvec2 *offset)
{
	box->x = minmax.z - minmax.x;
	box->y = minmax.w - minmax.y;
	offset->x = -minmax.x;
	offset->y = minmax.w;
}

static void minmax_check(t_fvec4 tmp, t_fvec4 *minmax)
{
	if (tmp.x < minmax->x)
		minmax->x = tmp.x;
	if (tmp.x > minmax->z)
		minmax->z = tmp.x;
	if (tmp.y < minmax->y)
		minmax->y = tmp.y;
	if (tmp.y > minmax->w)
		minmax->w = tmp.y;
}

void calc_map_box(t_scene *sc, t_fvec2 *box, t_fvec2 *offset)
{
	t_vec2 pos;
	t_fvec4 tmp;
	t_fvec4 minmax;

	minmax = (t_fvec4){0, 0, 0, 0};
	pos.y = 0;
	while (pos.y < sc->map_size.y)
	{
		pos.x = 0;
		while (pos.x < sc->map_size.x)
		{
			tmp = (t_fvec4){pos.x, sc->map[pos.y][pos.x], pos.y, 1};
			tmp = mat_mult_vec(sc->cam.vp, tmp);
			minmax_check(tmp, &minmax);
			++pos.x;
		}
		++pos.y;
	}
	calc_map_box_2(minmax, box, offset);
}

t_mat4 get_map_mat(float scale, t_fvec2 offset, t_fvec2 box)
{
	t_mat4 dst;

	(void) box;
	(void) offset;
	dst = mat_id();
	scale = scale;
	dst.m[0][0] = scale;
	dst.m[1][1] = scale;
	dst.m[2][2] = scale;
	return (dst);
}
