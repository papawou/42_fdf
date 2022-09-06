/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:15:35 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 03:15:35 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_H
# define FTMLX_H

# include <mlx.h>

# include "libftmlx/ftmlx_color.h"
# include "libftmlx/ftmlx_math.h"

typedef void	*t_mlx;
typedef void	*t_mlx_win;
typedef void	*t_mlx_img;

typedef struct s_img
{
	t_mlx_img	img;
	char		*addr;
	int			height;
	int			width;
	int			bpp;
	int			size_line;
	int			endian;
}	t_img;

typedef struct s_ftmlx
{
	t_mlx		mlx;
	t_mlx_win	win;
	t_vec2		wh;
}	t_ftmlx;

t_img	*ftmlx_new_img(t_mlx mlx, int x, int y);
void	ftmlx_free_img(t_mlx mlx, t_img *img);
int		*ftmlx_img_get_pxl(t_img *img, int x, int y);
void	ftmlx_img_set_pxl_color(t_img *img, int x, int y, int color);
void	ftmlx_img_put_img(t_img *src, t_img *dst, int dst_x, int dst_y);
void	fill_img(t_img *img, t_color c);
int		ftmlx_init(int width, int height, t_ftmlx *ftmlx);

#endif