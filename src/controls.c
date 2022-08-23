/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/23 06:28:37 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
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

/*
#define XK_Left 123
#define XK_Right 124
#define XK_Down 125
#define XK_Up 126
#define XK_Escape 100
*/

int	controls_camera_listener(int keycode, t_scene *sc)
{
	if (keycode == XK_Left)
	{
		world_rotate_camera(axisg_to_quat((t_axisg){0, 1, 0, 1}), &sc->cam);
	}
	if (keycode == XK_Right)
		world_rotate_camera(axisg_to_quat((t_axisg){0, 1, 0, -1}), &sc->cam);
	if (keycode == XK_Up)
		fps_rotate_camera(axisg_to_quat((t_axisg){1, 0, 0, 1}), &sc->cam);
	if (keycode == XK_Down)
		fps_rotate_camera(axisg_to_quat((t_axisg){1, 0, 0, -1}), &sc->cam);
	if (keycode == XK_a)
		fps_move_camera((t_fvec3){-1, 0, 0}, &sc->cam);
	if (keycode == XK_d)
		fps_move_camera((t_fvec3){1, 0, 0}, &sc->cam);
	if (keycode == XK_w)
		fps_move_camera((t_fvec3){0, 0, -1}, &sc->cam);
	if (keycode == XK_s)
		fps_move_camera((t_fvec3){0, 0, 1}, &sc->cam);
	if (keycode == XK_space)
		world_move_camera((t_fvec3){0, 1, 0}, &sc->cam);
	if (keycode == XK_z)
		world_move_camera((t_fvec3){0, -1, 0}, &sc->cam);
	if (keycode == XK_q)
	{
		//world_rotate_camera((t_fvec3){35.264, 45, 0}, &sc->cam);
	}
	ftmlx_update_cam(&sc->cam);
	return (0);
}
