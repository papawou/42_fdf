/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:49 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/22 03:33:52 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <libftmlx.h>
# include <math.h>

#include "parser.h"

typedef struct s_scene
{
	t_ftmlx		ft;
	t_ftcam		cam;
	t_ftmlx3d	ft3d;
	t_img		*canvas;

	int			**map;
	t_color	**map_color;
	t_transform	tr_map;
	t_fvec2		map_size;
	float		**depth_buffer;
}	t_scene;

void	draw_map_wire(t_scene *sc);
void	draw_map_triangle(t_scene *sc);

int		shader_map_wire(t_fvec4 a, t_fvec4 b, t_scene *sc);
void	shader_map(t_fvec3 a, t_fvec3 b, t_fvec3 c, t_scene *sc);

void	setup_cam(t_scene *sc);
int		controls_camera_listener(int keycode, t_scene *sc);

//scene.c
void exit_clean(int code, char *str);
void	init_sc(t_scene *sc);
void	clean_scene(int code, t_scene *sc);

//cleaner.c
void	clean_exit(int code_exit, t_scene *sc);
int	close_me(void);

//parser_cleaner.c
void clean_fd_map(enum e_code_clean code, int fd_map);
void clean_book(int code, t_list **entry);

//parser.c
char	*get_next_line(int fd);
int		parse_map(char *map_path, t_scene *sc);
int		parse_line(char *s, int dst[], t_color map_color[]);

#endif