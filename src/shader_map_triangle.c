#include <libftmlx.h>
#include "fdf.h"
#include "lib_utils.h"

typedef struct s_frag
{
	t_vec2 pos;
	t_color c;
	// lerp?
} t_frag;

static void shader_frag(t_frag frag, t_scene *sc)
{
	ftmlx_img_set_pxl_color(sc->canvas, frag.pos.x, frag.pos.y, ftmlx_get_color_int(frag.c));
}

static t_frag shader_inter(t_frag fa, t_frag fb, t_frag fc, t_vec2 point)
{
	t_frag frag;
	t_fvec3 w;

	w = tri_point_bar(fa.pos, fb.pos, fc.pos, point);
	frag.pos = point;
	frag.c = fa.c;
	return frag;
}

int shader_map_triangle(t_fvec4 a, t_fvec4 b, t_fvec4 c, t_scene *sc, t_color color)
{
	t_frag fa;
	t_frag fb;
	t_frag fc;
	t_rast_tri rast;

	// backface culling
	// vertex_shader

	t_fvec2 tmp_a;
	t_fvec2 tmp_b;
	t_fvec2 tmp_c;

	if (vertex_to_screen(a, &tmp_a, *sc->ft3d.proj, *sc->ft3d.wh))
		return 1;
	if (vertex_to_screen(b, &tmp_b, *sc->ft3d.proj, *sc->ft3d.wh))
		return 1;
	if (vertex_to_screen(c, &tmp_c, *sc->ft3d.proj, *sc->ft3d.wh))
		return 1;

	fa.c = color;
	fa.pos.x = tmp_a.x;
	fa.pos.y = tmp_a.y;
	fb.pos.x = tmp_b.x;
	fb.pos.y = tmp_b.y;
	fc.pos.x = tmp_c.x;
	fc.pos.y = tmp_c.y;
	rast = ftmlx_raster_tri(fa.pos, fb.pos, fc.pos);

	unsigned int line;
	unsigned int i;
	line = 0;
	while (line < rast.len)
	{
		i = 0;
		while (i < rast.lines[line].len)
		{
			shader_frag(shader_inter(fa, fb, fc, rast.lines[line].points[i]), sc);
			++i;
		}
		++line;
	}
	return 0;

	free_rast_tri(rast);
}
