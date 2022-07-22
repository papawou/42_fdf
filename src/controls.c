/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/07/22 03:37:35 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include "fdf.h"

void	fps_lrotate_camera(t_quat q, t_ftcam *cam)
{
	cam->tranf = transform_mult_quat(cam->tranf, q);
}

void	fps_lmove_camera(t_fvec3 v, t_ftcam *cam)
{
	cam->tranf = transform_mult_vec(cam->tranf, v);
}
void	fps_wmove_camera(t_fvec3 v, t_ftcam *cam)
{
	cam->tranf = vec_mult_transform(v, cam->tranf);
}


void	fps_wrotate_camera(t_quat q, t_ftcam *cam)
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
		fps_wrotate_camera(axisg_to_quat((t_axisg){0, 1, 0, 1}), &sc->cam);
	if (keycode == XK_Right)
		fps_wrotate_camera(axisg_to_quat((t_axisg){0, 1, 0, -1}), &sc->cam);
	if (keycode == XK_Up)
		fps_lrotate_camera(axisg_to_quat((t_axisg){1, 0, 0, 1}), &sc->cam);
	if (keycode == XK_Down)
		fps_lrotate_camera(axisg_to_quat((t_axisg){1, 0, 0, -1}), &sc->cam);
	if (keycode == XK_a)
		fps_lmove_camera((t_fvec3){-1, 0, 0} , &sc->cam);
	if (keycode == XK_d)
		fps_lmove_camera((t_fvec3){1, 0, 0} , &sc->cam);
	if (keycode == XK_w)
		fps_lmove_camera((t_fvec3){0, 0, -1}, &sc->cam);
	if (keycode == XK_s)
		fps_lmove_camera((t_fvec3){0 ,0 ,1}, &sc->cam);
	if (keycode == XK_space)
		fps_wmove_camera((t_fvec3){0, 1, 0}, &sc->cam);
	if (keycode == XK_z)
		fps_wmove_camera((t_fvec3){0, -1, 0}, &sc->cam);
	ftmlx_update_cam(&sc->cam);
	return (0);
}