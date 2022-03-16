#include "fdf.h"

void draw_map_wire(t_scene *sc)
{
	int **map;
	int x = 0;
	int z = 0;

	map = sc->map;
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			if (x < sc->map_size.x - 1)
				shader_map_wire((t_fvec4){x, map[z][x], z, 1}, (t_fvec4){x + 1, map[z][x + 1], z, 1}, sc);
			if (z < sc->map_size.y - 1)
				shader_map_wire((t_fvec4){x, map[z][x], z, 1}, (t_fvec4){x, map[z + 1][x], z + 1, 1}, sc);
			++x;
		}
		++z;
	}
}

void draw_map_triangle(t_scene *sc) // shader_mesh
{
	t_fvec3 a, b, c;
	int **map;
	int x = 0;
	int z = 0;

	map = sc->map;
	while (z < sc->map_size.y - 1)
	{
		x = 0;
		while (x < sc->map_size.x - 1)
		{
			a = (t_fvec3){x, map[z][x], z};
			b = (t_fvec3){x, map[z + 1][x], z + 1};
			c = (t_fvec3){x + 1, map[z][x + 1], z};
			shader_map(a, b, c, sc);
			a = (t_fvec3){x + 1, map[z + 1][x + 1], z + 1};
			shader_map(c, b, a, sc);
			++x;
		}
		++z;
	}
	/*
	t_fvec3 a, b, c;

	a = (t_fvec3){1, 0, 0};
	b = (t_fvec3){2, 0, 0};
	c = (t_fvec3){1, 1, -1};
	shader_map(a, b, c, sc);

	a = (t_fvec3){-1, 0, 0};
	b = (t_fvec3){0, 0, 0};
	c = (t_fvec3){-1, 1, -1};
	shader_map(a, b, c, sc);
	*/
}
