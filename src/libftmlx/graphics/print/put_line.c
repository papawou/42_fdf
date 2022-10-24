/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:56:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/06 21:01:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx.h"

typedef struct s_bresen_vars
{
	int		delta;
	int		threshold;
	int		thresholdinc;
	int		i;
	int		range;
	t_vec2	pt;
	int		swap;
	int		offset;
	int		adjust;
}	t_bresen_vars;

typedef struct s_bresen_params
{
	t_vec2	a;
	t_vec2	b;
	int		adjust;
	int		rise;
	int		run;
}	t_bresen_params;

static void	plot_loop_x(t_bresen_vars *v, t_color c[2], t_img *canvas)
{
	t_color	c_pt;

	v->range += 1;
	while (v->i < v->range)
	{
		if (v->swap)
			c_pt = ftmlx_lerp_color(c[1], c[0], (float)v->i / v->range);
		else
			c_pt = ftmlx_lerp_color(c[0], c[1], (float)v->i / v->range);
		ftmlx_img_set_pxl_color(canvas, v->pt.x + v->i, v->pt.y,
			ftmlx_get_color_int(c_pt));
		v->offset += v->delta;
		if (v->offset >= v->threshold)
		{
			v->pt.y += v->adjust;
			v->threshold += v->thresholdinc;
		}
		++v->i;
	}
}

static void	plot_line_x(t_bresen_params *p, t_color c[2], t_img *canvas)
{
	t_bresen_vars	v;

	v.pt.x = p->a.x;
	v.pt.y = p->a.y;
	v.swap = 0;
	if (p->b.x < p->a.x)
	{
		v.pt.x = p->b.x;
		v.pt.y = p->b.y;
		v.swap = 1;
	}
	v.delta = ft_abs(p->rise) * 2;
	v.threshold = ft_abs(p->run);
	v.thresholdinc = ft_abs(p->run) * 2;
	v.offset = 0;
	v.adjust = p->adjust;
	v.i = 0;
	v.range = ft_abs(p->b.x - p->a.x);
	plot_loop_x(&v, c, canvas);
}

static void	plot_loop_y(t_bresen_vars *v, t_color c[2], t_img *canvas)
{
	t_color	c_pt;

	v->range += 1;
	while (v->i < v->range)
	{
		if (v->swap)
			c_pt = ftmlx_lerp_color(c[1], c[0], (float)v->i / v->range);
		else
			c_pt = ftmlx_lerp_color(c[0], c[1], (float)v->i / v->range);
		ftmlx_img_set_pxl_color(canvas, v->pt.x, v->pt.y + v->i,
			ftmlx_get_color_int(c_pt));
		v->offset += v->delta;
		if (v->offset >= v->threshold)
		{
			v->pt.x += v->adjust;
			v->threshold += v->thresholdinc;
		}
		++v->i;
	}
}

static void	plot_line_y(t_bresen_params *p, t_color c[2], t_img *canvas)
{
	t_bresen_vars	v;

	v.pt.x = p->a.x;
	v.pt.y = p->a.y;
	v.swap = 0;
	if (p->b.y < p->a.y)
	{
		v.pt.x = p->b.x;
		v.pt.y = p->b.y;
		v.swap = 1;
	}
	v.delta = ft_abs(p->run) * 2;
	v.threshold = ft_abs(p->rise);
	v.thresholdinc = ft_abs(p->rise) * 2;
	v.i = 0;
	v.range = ft_abs(p->b.y - p->a.y);
	v.offset = 0;
	v.adjust = p->adjust;
	plot_loop_y(&v, c, canvas);
}

void	ftmlx_put_bresen_line(t_vec2 a, t_vec2 b, t_color c[2], t_img *canvas)
{
	float			m;
	t_bresen_params	p;

	p.a = a;
	p.b = b;
	p.rise = p.b.y - p.a.y;
	p.run = p.b.x - p.a.x;
	m = (float)p.rise / p.run;
	p.adjust = 1;
	if (m < 0)
		p.adjust = -1;
	if (m <= 1 && m >= -1)
		plot_line_x(&p, c, canvas);
	else
		plot_line_y(&p, c, canvas);
}
