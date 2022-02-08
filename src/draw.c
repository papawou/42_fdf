#include "fdf.h"

void put_vertex(t_vec4 v, t_color c, t_scene *sc)
{
	t_vec4 ndc = get_vertex_ndc(v, sc);
	if (!check_vertex_ndc(ndc))
	{
		ft_putstr_fd("OUT\n", 1);
		return;
	}
	t_vec2 screen = ndc_to_screen(ndc, sc);
	ftmlx_img_set_pxl_color(sc->canvas, screen.x, screen.y, ftmlx_get_color_int(c));
}

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
	t_vec2 tmp_a = ndc_to_screen(get_vertex_ndc(a, sc), sc);
	t_vec2 tmp_b = ndc_to_screen(get_vertex_ndc(b, sc), sc);
	draw_line(tmp_a, tmp_b, (t_color){255, 0, 0, 0}, sc);
	tmp_a = ndc_to_screen(get_vertex_ndc((t_vec4){a.x, 0, a.z, 1}, sc), sc);
	tmp_b = ndc_to_screen(get_vertex_ndc((t_vec4){b.x, 0, b.z, 1}, sc), sc);
	draw_line(tmp_a, tmp_b, (t_color){255, 0, 0, 0}, sc);

	tmp_a = ndc_to_screen(get_vertex_ndc((t_vec4){a.x, 0, a.z, 1}, sc), sc);
	tmp_b = ndc_to_screen(get_vertex_ndc((t_vec4){a.x, a.y, a.z, 1}, sc), sc);
	draw_line(tmp_a, tmp_b, (t_color){255, 0, 0, 0}, sc);
}

void draw_column(t_vec4 org, t_scene *sc)
{
	int off = 1;
	draw_face(org, (t_vec4){org.x + off, org.y, org.z, 1}, sc); //->tl tr br bl ...tl
	draw_face((t_vec4){org.x + off, org.y, org.z, 1}, (t_vec4){org.x + off, org.y, org.z + off, 1}, sc);
	draw_face((t_vec4){org.x + off, org.y, org.z + off, 1}, (t_vec4){org.x, org.y, org.z + off, 1}, sc);
	draw_face((t_vec4){org.x, org.y, org.z + off, 1}, org, sc);
}

void print_axis(t_scene *sc)
{
	t_vec2 org;
	t_vec2 tail;

	org = ndc_to_screen(get_vertex_ndc((t_vec4){0, 0, 0, 1}, sc), sc);
	tail = ndc_to_screen(get_vertex_ndc((t_vec4){20, 0, 0, 1}, sc), sc);
	put_vertex((t_vec4){20, 0, 0, 1}, (t_color){255, 0, 0, 0}, sc);
	draw_line(org, tail, (t_color){255, 0, 0, 0}, sc);

	put_vertex((t_vec4){0, 20, 0, 1}, (t_color){0, 255, 0, 0}, sc);
	tail = ndc_to_screen(get_vertex_ndc((t_vec4){0, 20, 0, 1}, sc), sc);
	draw_line(org, tail, (t_color){0, 255, 0, 0}, sc);

	put_vertex((t_vec4){0, 0, 20, 1}, (t_color){0, 0, 255, 0}, sc);
	tail = ndc_to_screen(get_vertex_ndc((t_vec4){0, 0, 20, 1}, sc), sc);
	draw_line(org, tail, (t_color){0, 0, 255, 0}, sc);
}

void draw_line(t_vec2 a, t_vec2 b, t_color c, t_scene *sc)
{
	int dx;
	int dy;
	int steps;
	float x_step;
	float y_step;
	int i;
	float x;
	float y;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (ft_abs(dx) < ft_abs(dy))
		steps = ft_abs(dy);
	else
		steps = ft_abs(dx);
	x_step = (float)dx / steps;
	y_step = (float)dy / steps;
	i = 0;
	x = a.x;
	y = a.y;
	while (i < steps)
	{
		ftmlx_img_set_pxl_color(sc->canvas, x, y, ftmlx_get_color_int(c));
		x += x_step;
		y += y_step;
		++i;
	}
}