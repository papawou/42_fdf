/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 04:31:37 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"

void free_map(int **map, int nb_lines)
{
	while (nb_lines--)
		free(map[nb_lines]);
	free(map);
}

void parse_line(char *s, int dst[])
{
	int i = 0;
	int j = 0;

	while (s[j] && s[j] != '\n')
	{
		dst[i] = ft_atoi(s + j);
		while (s[j] && !ft_isspace(s[j]))
			++j;
		while (ft_isspace(s[j]))
			++j;
		++i;
	}
}

int count_words(char *line)
{
	int count = 0;

	while (*line)
	{
		if (!ft_isspace(*line))
		{
			++count;
			while (*line && !ft_isspace(*line))
				++line;
		}
		while (ft_isspace(*line))
			++line;
	}
	return count;
}

int count_lines(int fd_map, char *line)
{
	int count = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd_map);
		++count;
	}
	return count;
}

int parse_map(char *map_path, t_scene *sc)
{
	char *line;
	int fd_map;
	int i;

	fd_map = open(map_path, O_RDONLY);
	line = get_next_line(fd_map);
	sc->map_size.x = count_words(line);
	sc->map_size.y = count_lines(fd_map, line);
	sc->map = (int **)malloc(sizeof(int *) * sc->map_size.y);
	close(fd_map);
	fd_map = open(map_path, O_RDONLY);
	line = get_next_line(fd_map);
	i = 0;
	while (line)
	{
		sc->map[i] = (int *)malloc(sc->map_size.x * sizeof(int));
		parse_line(line, sc->map[i]);
		free(line);
		++i;
		line = get_next_line(fd_map);
	}
	close(fd_map);
	sc->tr_map.q = (t_quat)QUAT_ID;
	sc->tr_map.v = (t_fvec3){0, 0, 0};
	return 0;
}