/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:59:48 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 03:02:47 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libftmlx/math/ftmlx_vec.h"

float	fvec4_magn(t_fvec4 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_fvec4	fvec4_norm(t_fvec4 v)
{
	float	div_magn;

	div_magn = 1.0 / fvec4_magn(v);
	return ((t_fvec4){v.x * div_magn, v.y * div_magn,
		v.z * div_magn, v.w * div_magn});
}

t_fvec3	fvec3_inv(t_fvec3 v)
{
	return ((t_fvec3){-v.x, -v.y, -v.z});
}

t_fvec3	fvec3_add(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

float	fvec3_magn(t_fvec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
