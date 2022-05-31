/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:18 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 04:32:10 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_camera(t_quat q, t_ftcam *cam)
{
	cam->tranf = quat_mult_transform(q, cam->tranf);
	ftmlx_update_cam(cam);
}
