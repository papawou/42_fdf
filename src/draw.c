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
	process_line(a, b, (t_color){255, 0, 0, 0}, sc);
	process_line((t_vec4){a.x, 0, a.z, 1}, (t_vec4){b.x, 0, b.z, 1}, (t_color){255, 0, 0, 0}, sc);
	process_line((t_vec4){a.x, 0, a.z, 1}, (t_vec4){a.x, a.y, a.z, 1}, (t_color){255, 0, 0, 0}, sc);
}

void draw_column(t_vec4 org, t_scene *sc)
{
	int off = 1; //->tl tr br bl ...tl
	draw_face(org, (t_vec4){org.x + off, org.y, org.z, 1}, sc);
	draw_face((t_vec4){org.x + off, org.y, org.z, 1}, (t_vec4){org.x + off, org.y, org.z + off, 1}, sc);
	draw_face((t_vec4){org.x + off, org.y, org.z + off, 1}, (t_vec4){org.x, org.y, org.z + off, 1}, sc);
	draw_face((t_vec4){org.x, org.y, org.z + off, 1}, org, sc);
}

void draw_axis(t_scene *sc)
{
	float off = 1.0;

	process_line((t_vec4){0, 0, 0, 1}, (t_vec4){off, 0, 0, 1}, (t_color){255, 0, 0, 0}, sc);
	process_line((t_vec4){0, 0, 0, 1}, (t_vec4){0, off, 0, 1}, (t_color){0, 255, 0, 0}, sc);
	process_line((t_vec4){0, 0, 0, 1}, (t_vec4){0, 0, off, 1}, (t_color){0, 0, 255, 0}, sc);
}

void put_dda_line(t_vec2 a, t_vec2 b, t_color c, t_scene *sc)
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

void put_naive_line(t_vec2 a, t_vec2 b, t_color c, t_scene *sc)
{
	int tmp;
	int dx;
	int dy;
	float m;
	float mb;

	dx = b.x - a.x;
	dy = b.y - a.y;

	if (a.x == b.x)
	{
		if (b.y < a.y)
		{
			tmp = a.y;
			a.y = b.y;
			b.y = tmp;
		}
		while (a.y < b.y)
		{
			ftmlx_img_set_pxl_color(sc->canvas, a.x, a.y, ftmlx_get_color_int(c));
			++a.y;
		}
		return;
	}
	m = (float)dy / dx;
	mb = a.y - a.x * m;
	if (-1.0 <= m && m <= 1.0)
	{
		if (b.x < a.x)
		{
			tmp = a.x;
			a.x = b.x;
			b.x = tmp;
		}
		while (a.x < b.x)
		{
			ftmlx_img_set_pxl_color(sc->canvas, a.x, a.x * m + mb, ftmlx_get_color_int(c));
			++a.x;
		}
	}
	else
	{
		if (b.y < a.y)
		{
			tmp = a.y;
			a.y = b.y;
			b.y = tmp;
		}
		while (a.y < b.y)
		{
			ftmlx_img_set_pxl_color(sc->canvas, (a.y - mb) / m, a.y, ftmlx_get_color_int(c));
			++a.y;
		}
	}
}

void put_bresen_line(t_vec2 a, t_vec2 b, t_color c, t_scene *sc)
{
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	int tmp;

	if (dx == 0)
	{
		if (b.y < a.y)
		{
			tmp = a.y;
			a.y = b.y;
			b.y = tmp;
		}
		while (a.y < b.y)
		{
			ftmlx_img_set_pxl_color(sc->canvas, a.x, a.y, ftmlx_get_color_int(c));
			++a.y;
		}
		return;
	}

	int inc_offset;
	int offset = 0;
	int threshold;
	int threshold_inc;
	int inc_axis;
	float m = (float)dy / dx;

	dx = ft_abs(dx);
	dy = ft_abs(dy);
	if (m < 0)
		inc_axis = -1;
	else
		inc_axis = 1;
	if (-1.0 <= m && m <= 1.0)
	{
		inc_offset = dy * 2;
		threshold = dx;
		threshold_inc = dx * 2;
		if (b.x < a.x)
		{
			tmp = a.x;
			a.x = b.x;
			b.x = tmp;
			a.y = b.y;
		}
		while (a.x < b.x)
		{
			ftmlx_img_set_pxl_color(sc->canvas, a.x, a.y, ftmlx_get_color_int(c));
			offset += inc_offset;
			if (offset >= threshold)
			{
				a.y += inc_axis;
				threshold += threshold_inc;
			}
			++a.x;
		}
	}
	else
	{
		inc_offset = dx * 2;
		threshold = dy;
		threshold_inc = dy * 2;
		if (b.y < a.y)
		{
			tmp = a.y;
			a.y = b.y;
			b.y = tmp;
			a.x = b.x;
		}
		while (a.y < b.y)
		{
			ftmlx_img_set_pxl_color(sc->canvas, a.x, a.y, ftmlx_get_color_int(c));
			offset += inc_offset;
			if (offset >= threshold)
			{
				a.x += inc_axis;
				threshold += threshold_inc;
			}
			++a.y;
		}
	}
}