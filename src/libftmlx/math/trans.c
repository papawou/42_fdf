/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:56:25 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/29 13:06:48 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx/math/ftmlx_trans.h"

t_transform	transform_inv(t_transform t)
{
	t_transform	dst;

	dst.q = quat_inv(t.q);
	dst.v = fvec3_inv(quat_mult_vec(dst.q, t.v));
	return (dst);
}

t_mat4	transform_to_mat(t_transform t)
{
	t_mat4	m;

	m = quat_to_mat(t.q);
	m.m[0][3] = t.v.x;
	m.m[1][3] = t.v.y;
	m.m[2][3] = t.v.z;
	return (m);
}

t_transform	transform_mult(t_transform a, t_transform b)
{
	t_transform	dst;

	dst.q = quat_mult(a.q, b.q, 1);
	dst.v = fvec3_add(a.v, quat_mult_vec(a.q, b.v));
	return (dst);
}
