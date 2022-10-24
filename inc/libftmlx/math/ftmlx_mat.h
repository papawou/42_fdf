/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_mat.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:11:28 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/25 02:50:41 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_MAT_H
# define FTMLX_MAT_H

# include "libftmlx/math/ftmlx_vec.h"

typedef struct s_mat4
{
	float	m[4][4];
}	t_mat4;

t_fvec4	mat_mult_vec(t_mat4 m, t_fvec4 v);
t_mat4	mat_mult(t_mat4 a, t_mat4 b);
t_mat4	mat_id(void);
#endif