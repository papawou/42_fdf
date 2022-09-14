/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/14 13:56:43 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <libftmlx.h>
# include <math.h>

# include	"parser.h"

typedef struct s_scene
{
	t_ftmlx		ft;
	t_ftcam		cam;
	t_img		*canvas;

	int			**map;
	t_color		**map_color;
	t_vec2		map_size;
	t_mat4		map_mat;
}	t_scene;

//draw.c
void	draw(t_scene *sc);

void	setup_cam(t_scene *sc);
int		controls_camera_listener(int keycode, t_scene *sc);

//scene.c
void	exit_clean(int code, char *str);
void	init_sc(t_scene *sc);
void	clean_scene(int code, t_scene *sc);
void	setup_scene(t_scene *sc);

//cleaner.c
void	clean_exit(int code_exit, t_scene *sc);
int		close_me(t_scene *sc);

//parser_cleaner.c
void	clean_fd_map(enum e_code_clean code, int fd_map);
void	clean_book(int code, t_list **entry);

//parser.c
char	*get_next_line(int fd);
void	parse_map(char *map_path, t_scene *sc);
int		parse_line(char *s, int dst[], t_color map_color[]);
int		ft_atoi_safe(char *str, int *dst);

//map.c
void	calc_map_box(t_fvec2 *height, t_fvec2 *width, t_scene *sc);
t_mat4	scale_map_mat(float scale);

//cam.c
void	setup_cam(t_scene *sc);

//controls.c
void	fps_move_camera(t_fvec3 v, t_ftcam *cam);
void	world_move_camera(t_fvec3 v, t_ftcam *cam);

#endif