/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:56:23 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/29 13:06:39 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmlx/math/ftmlx_trans.h"

t_transform	quat_mult_transform(t_quat q, t_transform t)
{
	t_transform	dst;

	dst.q = quat_mult(q, t.q, 1);
	dst.v = quat_mult_vec(q, t.v);
	return (dst);
}

t_transform	vec_mult_transform(t_fvec3 v, t_transform t)
{
	t_transform	dst;

	dst.q = t.q;
	dst.v = fvec3_add(v, t.v);
	return (dst);
}

t_transform	transform_mult_quat(t_transform t, t_quat q)
{
	t_transform	dst;

	dst.q = quat_mult(t.q, q, 1);
	dst.v = t.v;
	return (dst);
}

t_transform	transform_mult_vec(t_transform t, t_fvec3 v)
{
	t_transform	dst;

	dst.q = t.q;
	dst.v = fvec3_add(t.v, quat_mult_vec(t.q, v));
	return (dst);
}
