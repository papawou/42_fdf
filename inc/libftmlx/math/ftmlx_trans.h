/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_trans.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:13:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/01 13:18:43 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_TRANS_H
# define FTMLX_TRANS_H

# include "libftmlx/math/ftmlx_mat.h"
# include "libftmlx/math/ftmlx_quat.h"
# include "libftmlx/math/ftmlx_vec.h"

typedef struct s_transform
{
	t_quat	q;
	t_fvec3	v;
}	t_transform;

t_transform	transform_inv(t_transform t);
t_mat4		transform_to_mat(t_transform t);
t_transform	transform_mult(t_transform a, t_transform b);
t_transform	transform_mult_quat(t_transform t, t_quat q);
t_transform	transform_mult_vec(t_transform t, t_fvec3 v);
t_transform	quat_mult_transform(t_quat q, t_transform t);
t_transform	vec_mult_transform(t_fvec3 v, t_transform t);

#endif