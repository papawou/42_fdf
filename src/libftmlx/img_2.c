/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:05:50 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/15 03:28:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftmlx.h"

void	ftmlx_img_put_img(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			ftmlx_img_set_pxl_color(dst, dst_x + x, dst_y + y,
				*ftmlx_img_get_pxl(src, x, y));
			++x;
		}
		++y;
	}
}

void	fill_img(t_img *img, t_color c)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ftmlx_img_set_pxl_color(img, x, y, ftmlx_get_color_int(c));
			++x;
		}
		++y;
	}
}

int	ftmlx_get_color_value(t_mlx mlx, int color)
{
	static t_mlx	p_mlx = NULL;

	if (mlx)
	{
		p_mlx = mlx;
		return (0);
	}
	if (p_mlx)
		return (mlx_get_color_value(p_mlx, color));
	return (0);
}
