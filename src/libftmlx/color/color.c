/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:48:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/15 03:27:15 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libftmlx.h"
#include "libftmlx/math/ftmlx_utils.h"
#include "libftmlx/ftmlx_color.h"

t_color	ftmlx_lerp_color(t_color a, t_color b, double alpha)
{
	t_color	color;

	color.a = ft_lerp(a.a, b.a, alpha);
	color.r = ft_lerp(a.r, b.r, alpha);
	color.g = ft_lerp(a.g, b.g, alpha);
	color.b = ft_lerp(a.b, b.b, alpha);
	return (color);
}

int	ftmlx_get_color_int(t_color color)
{
	return (color.a << 24 | color.r << 16 | color.g << 8 | color.b);
}

t_color	ftmlx_get_int_color(int color)
{
	t_color	c;

	c.a = color >> 24 & 0xFF;
	c.r = color >> 16 & 0xFF;
	c.g = color >> 8 & 0xFF;
	c.b = color & 0xFF;
	return (c);
}
