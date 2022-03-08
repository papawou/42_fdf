#include <libftmlx.h>
#include "fdf.h"

// model
// world
// view
// clip
// *persp divide*
// ndc
// screen

/*
typedef struct s_frag
{
	t_fvec4 pos;
	t_color c;
} t_frag;

static void shader_frag(t_frag frag, t_scene *sc)
{
	ftmlx_img_set_pxl_color(sc->canvas, frag.pos.x, frag.pos.y, ftmlx_get_color_int(frag.attr.c));
}

static t_frag shader_vertex(t_fvec3 v, t_scene *sc)
{
	t_frag f;

	f.pos.x = v.x;
	f.pos.y = v.y;
	f.pos.z = v.z;
	f.pos.w = 1;
	f.c = (t_color){255, 0, 0, 0};
	return f;
}

static void attr_mult(t_frag *f, float w)
{
	f->c.r *= w;
	f->c.g *= w;
	f->c.b *= w;
	f->c.a *= w;
}

static t_frag shader_inter(t_frag (*t)[3], t_vec2 v)
{
	t_frag f;
	t_fvec3 w;

	w = shader_pre_inter_tri((t_fvec4[3]){t[0]->pos, t[1]->pos, t[2]->pos},
													 (t_fvec2){v.x, v.y}, &f.pos);

	f.attr.c = color_barerp(t[0]->c, t[1]->c, t[2]->c, w);
	attr_mult(&f, f.pos.w);
	return f;
}

int shader_map_tri(t_fvec3 a, t_fvec3 b, t_fvec3 c, t_scene *sc)
{
	t_frag t[3];
	t_rast_tri rast;
	unsigned int line;
	unsigned int i;

	t[0] = shader_vertex(a, sc);
	t[1] = shader_vertex(b, sc);
	t[2] = shader_vertex(c, sc);
	if (post_vertex_tri((t_fvec4 *[3]){&t[0].pos, &t[1].pos, &t[2].pos}, sc))
		return 1;
	attr_mult(&t[0].attr, t[0].pos.w);
	attr_mult(&t[1].attr, t[1].pos.w);
	attr_mult(&t[2].attr, t[2].pos.w);
	rast = ftmlx_raster_tri((t_vec2){t[0].pos.x, t[0].pos.y}, (t_vec2){t[1].pos.x, t[1].pos.y},
													(t_vec2){t[2].pos.x, t[2].pos.y});
	line = 0;
	while (line < rast.len)
	{
		i = 0;
		while (i < rast.lines[line].len)
			shader_frag(shader_inter(&t, rast.lines[line++].points[i++]), sc);
	}
	free_rast_tri(rast);
	return 0;
}
*/

// client side

typedef struct s_frag_attr
{
	float alpha;
} t_frag_attr;

static void attr_mult(void *attr_ptr, float w)
{
	t_frag_attr *attr;

	attr = attr_ptr;
	attr->alpha *= w;
}

static void vertex_shader(t_frag *f)
{
	t_frag_attr *attr;

	attr = f->attr;
	attr->alpha = 1.0;
}

static void frag_inter(void *t_ptr[3], void *attr_ptr, t_fvec3 w)
{
	t_frag_attr **t;
	t_frag_attr *attr;

	attr = attr_ptr;
	t = (t_frag_attr **)t_ptr;
	attr->alpha = tri_barerp(t[0]->alpha, t[1]->alpha, t[2]->alpha, w);
}

static t_color frag_shader(t_frag *f)
{
	t_frag_attr *attr;
	t_color c;

	attr = f->attr;
	c = (t_color){255 * attr->alpha, 0, 0, 255};
	return c;
}

void shader_map(t_fvec3 a, t_fvec3 b, t_fvec3 c, t_scene *sc)
{ //?mat4 model
	t_shader shader;

	shader.attr_mult = attr_mult;
	shader.frag_inter = frag_inter;
	shader.vertex_shader = vertex_shader;
	shader.frag_shader = frag_shader;
	shader.attr_size = sizeof(t_frag_attr);

	shader.mvp = &sc->cam.vp;
	shader.wh = &sc->ft.wh;
	shader.canvas = sc->canvas;
	shader_tri((t_fvec3 *[3]){&a, &b, &c}, &shader);
}