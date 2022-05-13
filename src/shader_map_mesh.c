#include <libftmlx.h>
#include "fdf.h"
#include "libft/mem.h"
#include "libft.h"

// model
// world
// view
// clip
// *persp divide*
// ndc
// screen

int get_color_texture(float u, float v, t_mlx mlx)
{

	static t_img *text = NULL;
	int x;
	int y;

	if (text == NULL)
		text = ftmlx_new_xpm_img(mlx, "./bin/img/jlale.xpm");
	x = ft_lerp(0, text->width, u);
	y = ft_lerp(0, text->height, v);

	int c = *ftmlx_img_get_pxl(text, x, y);
	return c;
}

typedef struct s_frag_attr
{
	t_fvec2 uv;
	float y_world;
} t_frag_attr;

static void attr_mult(void *attr_ptr, float w)
{
	t_frag_attr *attr;

	attr = attr_ptr;

	attr->uv.x *= w;
	attr->uv.y *= w;

	attr->y_world *= w;
}

static void frag_inter(void *t_ptr[3], void *attr_ptr, t_fvec3 w)
{
	t_frag_attr **t;
	t_frag_attr *attr;

	t = (t_frag_attr **)t_ptr;
	attr = attr_ptr;
	attr->uv.x = tri_barerp(t[0]->uv.x, t[1]->uv.x, t[2]->uv.x, w);
	attr->uv.y = tri_barerp(t[0]->uv.y, t[1]->uv.y, t[2]->uv.y, w);

	attr->y_world = tri_barerp(t[0]->y_world, t[1]->y_world, t[2]->y_world, w);
}

static t_color frag_shader(t_frag *f, void *params)
{
	t_frag_attr *attr;
	t_scene *sc;

	sc = params;
	attr = f->attr;
	int c = get_color_texture(attr->uv.x, attr->uv.y, sc->ft.mlx);
	t_color test = ftmlx_get_int_color(c);
	test = ftmlx_lerp_color((t_color){0, 0, 0, 0}, test, attr->y_world);
	//test = (t_color) {255,255,255,0};
	return test;
}

static void vertex_shader(t_frag *f, void *params)
{
	t_frag_attr *attr;
	t_scene *sc;

	sc = params;
	attr = f->attr;

	attr->uv.x = f->coord.x / (sc->map_size.x - 1);
	attr->uv.y = f->coord.z / (sc->map_size.y - 1);

	attr->y_world = 1.0;
}

void shader_map(t_fvec3 a, t_fvec3 b, t_fvec3 c, t_scene *sc)
{ //?mat4 model
	static t_shader shader;
	static int test_init = 1;

	if (test_init)
	{
		shader.attr_mult = attr_mult;
		shader.frag_inter = frag_inter;
		shader.vertex_shader = vertex_shader;
		shader.frag_shader = frag_shader;
		shader.attr_size = sizeof(t_frag_attr);

		shader.mvp = &sc->cam.vp;
		shader.wh = &sc->ft.wh;
		shader.canvas = sc->canvas;
		shader.depth_buffer = sc->depth_buffer;

		shader.params = sc;
		test_init = 0;
	}
	shader_tri((t_fvec3 *[3]){&a, &b, &c}, &shader);
}