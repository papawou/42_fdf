/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:29 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/20 04:23:01 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
void	draw_map_wire(t_scene *sc)
{
	int	**map;
	int	x;
	int	z;

	x = 0;
	z = 0;
	map = sc->map;
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			if (x < sc->map_size.x - 1)
				shader_map_wire((t_fvec4){x, map[z][x], z, 1},
					(t_fvec4){x + 1, map[z][x + 1], z, 1}, sc);
			if (z < sc->map_size.y - 1)
				shader_map_wire((t_fvec4){x, map[z][x], z, 1},
					(t_fvec4){x, map[z + 1][x], z + 1, 1}, sc);
			++x;
		}
		++z;
	}
}
*/

void	draw_map_triangle(t_scene *sc)
{
	t_fvec3	t[3];
	int		**map;
	int		x;
	int		z;

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
