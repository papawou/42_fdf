/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/01 13:33:06 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <libftmlx.h>
# include <math.h>

typedef struct s_scene
{
	t_ftmlx		ft;
	t_ftcam		cam;
	t_ftmlx3d	ft3d;
	t_img		*canvas;
	int			**map;
	t_transform	tr_map;
	t_fvec2		map_size;
	float		**depth_buffer;
}	t_scene;

void	draw_map_wire(t_scene *sc);
void	setup_cam(t_scene *sc);
void	draw_map_triangle(t_scene *sc);
void	rotate_camera(t_quat q, t_ftcam *cam);
int		shader_map_wire(t_fvec4 a, t_fvec4 b, t_scene *sc);
void	shader_map(t_fvec3 a, t_fvec3 b, t_fvec3 c, t_scene *sc);
int		parse_map(char *map_path, t_scene *sc);
void	free_map(int **map, int nb_lines);
char	*get_next_line(int fd);

#endif