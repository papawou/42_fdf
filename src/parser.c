/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/19 15:52:07 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "fdf.h"

int	count_words(char *line)
{
	int	count;

	count = 0;
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
	return (count);
}

int	count_lines(int fd_map, char *line)
{
	int	count;

	count = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd_map);
		++count;
	}
	return (count);
}

void	parse_map_first_pass(char *map_path, t_scene *sc)
{
	char	*line;
	int		fd_map;

	fd_map = open(map_path, O_RDONLY);
	if (fd_map < 0)
		exit(EXIT_FAILURE);
	exit_clean_parser(0, (t_p_clean_parser){fd_map, NULL, NULL, 0});
	line = get_next_line(fd_map);
	sc->map_size.x = count_words(line);
	if (sc->map_size.x == 0)
	{
		free(line);
		exit_clean_parser(1, clean_parser_id());
	}
	sc->map_size.y = count_lines(fd_map, line);
	close(fd_map); //!!!
	sc->map = (int **)malloc(sizeof(int *) * sc->map_size.y);
	if (sc->map == NULL)
		exit(EXIT_FAILURE);
	sc->map_color = (t_color **)malloc(sizeof(t_color *) * sc->map_size.y);
	if (sc->map_color == NULL)
	{
		free(sc->map);
		exit(EXIT_FAILURE);
	}
}

void	parse_map_inline(char *line, int fd_map, t_scene *sc)
{
	int	i;

	i = 0;
	while (line)
	{
		sc->map[i] = (int *)malloc(sc->map_size.x * sizeof(int));
		if (sc->map[i] == NULL)
		{
			free(line);
			exit_clean_parser(2, (t_p_clean_parser){-1, NULL, NULL, i});
		}
		sc->map_color[i] = (t_color *)malloc(sc->map_size.x * sizeof(t_color));
		if (sc->map_color[i] == NULL)
		{
			free(line);
			free(sc->map[i]);
			exit_clean_parser(2, (t_p_clean_parser){-1, NULL, NULL, i});
		}
		exit_clean_parser(0, (t_p_clean_parser){-1, NULL, NULL, i + 1});
		if (parse_line(line, sc->map[i], sc->map_color[i])) //not tested;
		{
			free(line);
			exit_clean_parser(2, (t_p_clean_parser){-1, NULL, NULL, i});
		}
		free(line);
		++i;
		line = get_next_line(fd_map);
	}
}

int	parse_map(char *map_path, t_scene *sc)
{
	char	*line;
	int		fd_map;

	parse_map_first_pass(map_path, sc);
	fd_map = open(map_path, O_RDONLY);
	if (fd_map < 0)
	{
		free(sc->map);
		free(sc->map_color);
		exit(EXIT_FAILURE);
	}
	exit_clean_parser(0, (t_p_clean_parser){fd_map, sc->map, sc->map_color, 0});
	line = get_next_line(fd_map);
	parse_map_inline(line, fd_map, sc);
	close(fd_map);
	return (0);
}
