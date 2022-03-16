#include <libftmlx.h>
#include "fdf.h"

// model
// world
// view
// clip
// *persp divide*
// ndc
// screen

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
	attr->alpha = f->coord.x / 4.0;
}

static void frag_inter(void *t_ptr[3], void *attr_ptr, t_fvec3 w)
{
	t_frag_attr **t;
	t_frag_attr *attr;

	t = (t_frag_attr **)t_ptr;
	attr = attr_ptr;
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