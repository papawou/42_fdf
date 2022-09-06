/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_vec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:13:33 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/26 16:38:01 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_VEC_H
# define FTMLX_VEC_H

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_vec4
{
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vec4;

typedef struct s_fvec2
{
	float	x;
	float	y;
}	t_fvec2;

typedef struct s_fvec3
{
	float	x;
	float	y;
	float	z;
}	t_fvec3;

typedef struct s_fvec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_fvec4;

float	fvec4_magn(t_fvec4 v);
t_fvec4	fvec4_norm(t_fvec4 v);
t_fvec3	fvec3_inv(t_fvec3 v);
t_fvec3	fvec3_add(t_fvec3 a, t_fvec3 b);
float	fvec3_magn(t_fvec3 v);
t_fvec3	fvec3_norm(t_fvec3 v);
float	fvec3_dot(t_fvec3 a, t_fvec3 b);
t_fvec3	fvec3_cross(t_fvec3 a, t_fvec3 b);
t_fvec3	fvec3_minus(t_fvec3 a, t_fvec3 b);

#endif