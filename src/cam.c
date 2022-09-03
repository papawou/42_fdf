/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:38:13 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/31 01:00:08 by kmendes          ###   ########.fr       */
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
	//proj = ftmlx_create_x_persp_proj(60, sc->ft.wh.x / sc->ft.wh.y, 1000, 1);
	//proj = ftmlx_create_orth_proj(test, test, 1000, 1);
	proj = mat_id();
	ftmlx_init_cam(tranf, proj, &sc->cam);
}