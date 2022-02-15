#include "fdf.h"

void draw_map(t_scene *sc)
{
	int x = 0;
	int z = 0;
	while (z < sc->map_size.y)
	{
		x = 0;
		while (x < sc->map_size.x)
		{
			draw_column((t_vec4){x, sc->map[z][x], z, 1}, sc);
			++x;
		}
		++z;
	}
}

void draw_face(t_vec4 a, t_vec4 b, t_scene *sc)
{
	shader_map(a, b, sc);
	shader_map((t_vec4){a.x, 0, a.z, 1}, (t_vec4){b.x, 0, b.z, 1}, sc);
	shader_map((t_vec4){a.x, 0, a.z, 1}, (t_vec4){a.x, a.y, a.z, 1}, sc);
}

/*
void draw_face(t_vec4 a, t_vec4 b, t_scene *sc)
{
	ftmlx_put_line(sc->ft3d, a, b, (t_color){255, 0, 0, 0});
	ftmlx_put_line(sc->ft3d, (t_vec4){a.x, 0, a.z, 1}, (t_vec4){b.x, 0, b.z, 1}, (t_color){255, 0, 0, 0});
	ftmlx_put_line(sc->ft3d, (t_vec4){a.x, 0, a.z, 1}, (t_vec4){a.x, a.y, a.z, 1}, (t_color){255, 0, 0, 0});
}
*/

void draw_column(t_vec4 org, t_scene *sc)
{
	int off = 1; //->tl tr br bl ...tl
	draw_face(org, (t_vec4){org.x + off, org.y, org.z, 1}, sc);
	draw_face((t_vec4){org.x + off, org.y, org.z, 1}, (t_vec4){org.x + off, org.y, org.z + off, 1}, sc);
	draw_face((t_vec4){org.x + off, org.y, org.z + off, 1}, (t_vec4){org.x, org.y, org.z + off, 1}, sc);
	draw_face((t_vec4){org.x, org.y, org.z + off, 1}, org, sc);
}