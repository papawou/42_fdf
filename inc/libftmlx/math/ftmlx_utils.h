/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:57:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/14 13:57:27 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_UTILS_H
# define FTMLX_UTILS_H

# include <math.h>

# define PI 3.14159265358979323846

typedef struct s_remap_p
{
	float	input_a;
	float	input_b;
	float	out_a;
	float	out_b;
}	t_remap_p;

//utils.c
float	ft_clamp(float min, float max, float value);
float	ft_lerp(float start, float end, float alpha);
float	ft_invlerp(float start, float end, float value);
float	ft_remap(t_remap_p p, float value);

//utils_2.c
float	deg_to_rad(float deg);
float	rad_to_deg(float rad);
int		ft_abs(int a);
double	ft_fabs(double a);

#endif