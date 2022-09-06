/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmlx_cam.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 03:07:57 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/06 19:37:36 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMLX_CAM_H
# define FTMLX_CAM_H

# include "libftmlx.h"

typedef struct s_ftcam
{
	t_transform	tranf;
	t_mat4		vp;
	t_mat4		proj;
}	t_ftcam;

void	ftmlx_update_cam(t_ftcam *cam);
void	ftmlx_init_cam(t_transform tranf, t_mat4 src_proj,
			t_ftcam *cam);

#endif