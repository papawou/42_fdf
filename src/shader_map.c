#include <stdlib.h>
#include "fdf.h"
#include <libftmlx.h>
#include <libft.h>

typedef struct s_map_frag
{
	t_fvec2 pos;
	float grad_alpha;
} t_map_frag;

static t_map_frag shader_map_vertex(t_fvec4 v, t_scene *sc)
{
	t_map_frag fv;

	(void)sc;
	fv.grad_alpha = (float)v.y / 50;
	return fv;
}

static t_map_frag shader_map_lerp(t_map_frag fa, t_map_frag fb, t_fvec2 rast_point, double alpha)
{
	t_map_frag dst;

	dst.pos = rast_point;
	dst.grad_alpha = ft_lerp(fa.grad_alpha, fb.grad_alpha, alpha);
	return dst;
}

static void shader_map_frag(t_map_frag frag, t_scene *sc)
{
	static double keys[3] = {0.0, 0.5, 1.0};
	static t_color colors[3] = {{255, 0, 0, 0}, {0, 255, 0, 0}, {0, 0, 255, 0}};
	static t_gradient height_grad = {
			.len = 3,
			.keys = keys,
			.colors = colors};
	t_color c;

	c = ftmlx_get_gradient_color(&height_grad, frag.grad_alpha);
	ftmlx_img_set_pxl_color(sc->canvas, frag.pos.x, frag.pos.y, ftmlx_get_color_int(c));
}

int shader_map(t_fvec4 a, t_fvec4 b, t_scene *sc)
{
	t_map_frag fa;
	t_map_frag fb;
	t_raster rast;

	fa = shader_map_vertex(a, sc);
	fb = shader_map_vertex(b, sc);

	if (vertex_to_screen(a, &fa.pos, *sc->ft3d.proj, *sc->ft3d.wh))
		return 1;
	if (vertex_to_screen(b, &fb.pos, *sc->ft3d.proj, *sc->ft3d.wh))
		return 1;

	rast = ftmlx_raster_line(fa.pos, fb.pos);
	unsigned int i = 0;
	while (i < rast.len)
	{
		shader_map_frag(shader_map_lerp(fa, fb, rast.points[i], (double)i / rast.len), sc);
		++i;
	}
	return 0;
}