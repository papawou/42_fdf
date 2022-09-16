/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:33:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 15:41:57 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4	scale_map_mat(float scale)
{
	t_mat4	tmp;

	tmp = mat_id();
	tmp.m[0][0] = scale;
	tmp.m[1][1] = scale;
	tmp.m[2][2] = scale;
	return (tmp);
}

void	calc_map_box(t_fvec2 *height, t_fvec2 *width, t_scene *sc)
{
	t_vec2	pos;
	float	tmp;

	width->x = 0;
	width->y = (sqrt(2.0) / 2.0) * (sc->map_size.y + sc->map_size.x - 2);
	height->x = sc->map[sc->map_size.y - 1][sc->map_size.x - 1] * sqrt(2.0 / 3);
	height->y = height->x;
	pos.y = 0;
	while (pos.y < sc->map_size.y)
	{
		pos.x = 0;
		while (pos.x < sc->map_size.x)
		{
			tmp = (sc->map[pos.y][pos.x] * sqrt(2.0 / 3)
					+ (pos.x - pos.y) * (sqrt(2.0 / 3) / 2.0));
			if (tmp > height->y)
				height->y = tmp;
			else if (tmp < height->x)
				height->x = tmp;
			++pos.x;
		}
		++pos.y;
	}
}
