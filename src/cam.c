/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:38:13 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/14 06:30:30 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <libftmlx/ftmlx_math.h>

void	setup_cam(t_scene *sc)
{
	t_transform	tranf;
	t_mat4		proj;

	tranf = (t_transform){euler_to_quat((t_euler){-35.264, 45, 0}),
		(t_fvec3){0, 0, 0}};
	proj = mat_id();
	ftmlx_init_cam(tranf, proj, &sc->cam);
}
