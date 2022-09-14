/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:33:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/13 21:02:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
static void center_mat(t_scene *sc)
{
	sc->map_mat = mat_id();
	
	if (sc->map_size.x > 1)
		sc->map_mat.m[0][3] = -(sc->map_size.x - 1) / 2.0;
	if (sc->map_size.y > 1)
		sc->map_mat.m[2][3] = -(sc->map_size.y - 1) / 2.0;
}
*/

t_mat4 scale_map_mat(float scale, t_scene *sc)
{
	t_mat4 tmp;

	tmp = mat_id();
	tmp.m[0][0] = scale;
	tmp.m[1][1] = scale;
	tmp.m[2][2] = scale;
	(void) sc;
	//tmp = mat_mult(tmp, sc->map_mat);
	return (tmp);
}

void	calc_map_box(t_fvec2 *height, t_fvec2 *width, t_scene *sc)
{
	t_vec2	pos;
	float	tmp;

	width->x = -(sqrt(2.0) / 2.0) * (sc->map_size.y - 1);
	width->y = (sqrt(2.0) / 2.0) * (sc->map_size.x - 1);
	height->x = sc->map[0][0] * sqrt(2.0/3);
	height->y = height->x;
	pos.y = 0;
	while (pos.y < sc->map_size.y)
	{
		pos.x = 0;
		while (pos.x < sc->map_size.x)
		{
			tmp = (sc->map[pos.y][pos.x] * sqrt(2.0/3) - (pos.x + pos.y) * (sqrt(2.0/3)/2.0));
			if (tmp > height->y)
				height->y = tmp;
			else if (tmp < height->x)
				height->x = tmp;
			++pos.x;
		}
		++pos.y;
	}
}

