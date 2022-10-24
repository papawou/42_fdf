/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:48:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/01 13:19:45 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libftmlx/math/ftmlx_utils.h"
#include "libftmlx/math/ftmlx_rot.h"

t_quat	axisg_to_quat(t_axisg ag)
{
	t_quat	dst;

	ag.w = deg_to_rad(ag.w);
	dst.x = ag.x * sin(ag.w / 2);
	dst.y = ag.y * sin(ag.w / 2);
	dst.z = ag.z * sin(ag.w / 2);
	dst.w = cos(ag.w / 2);
	return (quat_norm(dst));
}

t_mat4	euler_to_mat(t_euler v)
{
	t_mat4	mat;
	float	x;
	float	y;
	float	z;

	x = v.x;
	y = v.y;
	z = v.z;
	mat = (t_mat4){{
	{cos(y) * cos(z), cos(z) * sin(x) * sin(y) - cos(x) * sin(z),
		cos(x) * cos(z) * sin(y) + sin(x) * sin(z), 0},
	{cos(y) * sin(z), cos(x) * cos(z) + sin(x) * sin(y) * sin(z),
		cos(x) * sin(y) * sin(z) - cos(z) * sin(x), 0},
	{-sin(y), cos(y) * sin(x), cos(x) * cos(y), 0}, {0, 0, 0, 1}}};
	return (mat);
}

typedef struct s_euler_to_quat_vars
{
	float	cz;
	float	sz;
	float	cy;
	float	sy;
	float	cx;
	float	sx;
}	t_euler_to_quat_vars;

t_quat	euler_to_quat(t_euler v)
{
	t_euler_to_quat_vars	v_;
	t_quat					q;

	v_.cz = cos(deg_to_rad(v.z) * 0.5);
	v_.sz = sin(deg_to_rad(v.z) * 0.5);
	v_.cy = cos(deg_to_rad(v.y) * 0.5);
	v_.sy = sin(deg_to_rad(v.y) * 0.5);
	v_.cx = cos(deg_to_rad(v.x) * 0.5);
	v_.sx = sin(deg_to_rad(v.x) * 0.5);
	q.w = v_.cx * v_.cy * v_.cz + v_.sx * v_.sy * v_.sz;
	q.x = v_.sx * v_.cy * v_.cz - v_.cx * v_.sy * v_.sz;
	q.y = v_.cx * v_.sy * v_.cz + v_.sx * v_.cy * v_.sz;
	q.z = v_.cx * v_.cy * v_.sz - v_.sx * v_.sy * v_.cz;
	return (quat_norm(q));
}
