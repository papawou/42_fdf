/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:59:31 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/01 13:15:14 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_COLOR_H
# define FTMLX_COLOR_H

# include "libftmlx/math/ftmlx_vec.h"

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_color;

t_color			ftmlx_lerp_color(t_color a, t_color b, double alpha);
int				ftmlx_get_color_int(t_color color);
t_color			ftmlx_get_int_color(int color);
t_color			color_barerp(t_color a, t_color b, t_color c, t_fvec3 w);

#endif