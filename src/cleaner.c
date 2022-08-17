/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:59:38 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/17 08:20:12 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

void	free_map(int **map, t_color **map_color, int nb_lines)
{
	while (nb_lines--)
	{
		free(map[nb_lines]);
		free(map_color[nb_lines]);
	}
	free(map);
	free(map_color);
}

t_p_clean_parser	clean_parser_id(void)
{
	return ((t_p_clean_parser){-1, NULL, NULL, 0});
}

void	exit_clean_parser(int code_exit, t_p_clean_parser params)
{
	static t_p_clean_parser	s = {-1, NULL, NULL, 0};

	if (code_exit == 2 || !code_exit)
	{
		if (params.fd_map != -1)
			s.fd_map = params.fd_map;
		if (params.map)
			s.map = params.map;
		if (params.map_color)
			s.map_color = params.map_color;
		if (params.i)
			s.i = params.i;
	}
	if (!code_exit)
		return ;
	if (s.fd_map)
		close(s.fd_map);
	free_map(s.map, s.map_color, s.i);
	exit(EXIT_FAILURE);
}

int	close_me(void)
{
	clean_exit(-1, NULL);
	return (0);
}

void	clean_exit(int code_exit, t_scene *sc)
{
	static t_scene	*p_sc = NULL;

	if (sc != NULL)
		p_sc = sc;
	if (!code_exit)
		return ;
	if (p_sc)
	{
		ft_free_malloc_cont_2d((void **)p_sc->depth_buffer);
		free_map(p_sc->map, p_sc->map_color, p_sc->map_size.y);
		ftmlx_free_img(p_sc->ft.mlx, p_sc->canvas);
		mlx_destroy_window(p_sc->ft.mlx, p_sc->ft.win);
		if (code_exit == -1)
			exit(0);
		else
			exit(EXIT_FAILURE);
	}
}
