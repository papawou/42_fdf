/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/17 16:24:45 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fps_move_camera(t_fvec3 v, t_ftcam *cam)
{
	v = quat_mult_vec(cam->tranf.q, v);
	cam->tranf = vec_mult_transform(v, cam->tranf);
}

void	world_move_camera(t_fvec3 v, t_ftcam *cam)
{
	cam->tranf = vec_mult_transform(v, cam->tranf);
}

void	fps_rotate_camera(t_quat q, t_ftcam *cam)
{
	cam->tranf = transform_mult_quat(cam->tranf, q);
}

void	world_rotate_camera(t_quat q, t_ftcam *cam)
{
	q = quat_mult(q, cam->tranf.q, 1);
	cam->tranf.q = q;
}
