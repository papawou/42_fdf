/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:03:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/15 03:22:13 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftmlx.h"

t_img	*ftmlx_new_img(t_mlx mlx, int x, int y)
{
	t_img	*img;

	img = (t_img *)malloc(sizeof(t_img));
	if (img == NULL)
		return (NULL);
	img->height = y;
	img->width = x;
	img->img = mlx_new_image(mlx, img->width, img->height);
	if (img->img == NULL)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian);
	return (img);
}

void	ftmlx_free_img(t_mlx mlx, t_img *img)
{
	if (img == NULL)
		return ;
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free(img);
}

int	*ftmlx_img_get_pxl(t_img *img, int x, int y)
{
	if (img->height <= y || img->width <= x || x < 0 || y < 0)
		return (NULL);
	return ((int *)(img->addr + (img->size_line * y + x * (img->bpp / 8))));
}

void	ftmlx_img_set_pxl_color(t_img *img, int x, int y, int color)
{
	int	i;
	int	pos;

	if (img->height <= y || img->width <= x || x < 0 || y < 0)
		return ;
	color = ftmlx_get_color_value(NULL, color);
	pos = (img->size_line * y + x * (img->bpp / 8));
	i = 0;
	while (i < (img->bpp / 8))
	{
		if (!img->endian)
			img->addr[pos + i] = (color >> (i * 8)) & 0xFF;
		else
			img->addr[pos + i] = (color >> ((sizeof(int) - 1 - i) * 8)) & 0xFF;
		++i;
	}
}
