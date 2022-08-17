/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:59:38 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/17 05:51:42 by kmendes          ###   ########.fr       */
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

t_p_clean_parser clean_parser_id(void)
{
	return ((t_p_clean_parser){-1, NULL, NULL, 0});
}

void	exit_clean_parser(int code_exit, t_p_clean_parser params)
{
	static t_p_clean_parser s = {-1, NULL, NULL, 0};

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