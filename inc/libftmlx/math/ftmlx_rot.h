/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_rot.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:12:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 03:12:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_ROT_H
# define FTMLX_ROT_H

# include "libftmlx/math/ftmlx_vec.h"
# include "libftmlx/math/ftmlx_quat.h"

typedef t_fvec3	t_euler;
typedef t_fvec4	t_axisg;

t_quat	axisg_to_quat(t_axisg ag);

t_mat4	euler_to_mat(t_euler v);
t_quat	euler_to_quat(t_euler v);

#endif