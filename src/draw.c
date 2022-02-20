#include "fdf.h"

void draw_map(t_scene *sc)
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
				shader_map((t_fvec4){x, map[z][x], z, 1}, (t_fvec4){x + 1, map[z][x + 1], z, 1}, sc);
			if (z < sc->map_size.y - 1)
				shader_map((t_fvec4){x, map[z][x], z, 1}, (t_fvec4){x, map[z + 1][x], z + 1, 1}, sc);
			++x;
		}
		++z;
	}
}

//2 triangles form square
//backface culling
//z depth buffer