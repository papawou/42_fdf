/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:37 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/06 20:54:58 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "fdf.h"

static void	parse_book(int **map, t_color **map_color, t_list *entry_page)
{
	t_list	*tmp_page;
	int		i;

	i = 0;
	tmp_page = entry_page;
	while (tmp_page)
	{
		if (parse_line(tmp_page->content, map[i], map_color[i]))
			exit_clean_parser();
		tmp_page = tmp_page->next;
		++i;
	}
}

static int	count_words(char *line)
{
	int	count;

	if (!line)
		return (0);
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

static int	count_map(t_list *entry_page, t_scene *sc)
{
	int		nb_cols;
	t_list	*curr_page;

	sc->map_size.x = count_words(entry_page->content);
	if (sc->map_size.x == 0)
		return (1);
	sc->map_size.y = 1;
	curr_page = entry_page->next;
	while (curr_page)
	{
		nb_cols = count_words(curr_page->content);
		if (nb_cols != sc->map_size.x)
			return (1);
		++sc->map_size.y;
		curr_page = curr_page->next;
	}
	return (0);
}

static void	parse_read_file(char *map_path, t_list **entry_page)
{
	t_list	*tmp_page;
	int		fd_map;
	char	*line;

	tmp_page = NULL;
	fd_map = open(map_path, O_RDONLY);
	if (fd_map < 0)
		exit_clean_parser();
	clean_fd_map(E_CODE_INIT, fd_map);
	line = get_next_line(fd_map);
	while (line)
	{
		tmp_page = ft_lstnew(line);
		if (!tmp_page)
		{
			free(line);
			exit_clean_parser();
		}
		ft_lstadd_back(entry_page, tmp_page);
		line = get_next_line(fd_map);
	}
	clean_fd_map(E_CODE_CLEAN | E_CODE_RESET, -1);
	return ;
}

void	parse_map(char *map_path, t_scene *sc)
{
	t_list	*entry_page;

	entry_page = NULL;
	clean_book(E_CODE_INIT, &entry_page);
	parse_read_file(map_path, &entry_page);
	if (!entry_page)
		exit_clean_parser();
	if (count_map(entry_page, sc))
		exit_clean_parser();
	sc->map = (int **)ft_malloc_cont_2d(sc->map_size.y,
			sc->map_size.x, sizeof(int));
	if (sc->map == NULL)
		exit_clean_parser();
	sc->map_color = (t_color **)ft_malloc_cont_2d(sc->map_size.y,
			sc->map_size.x, sizeof(t_color));
	if (sc->map_color == NULL)
	{
		ft_free_malloc_cont_2d((void **)sc->map);
		exit_clean_parser();
	}
	parse_book(sc->map, sc->map_color, entry_page);
	clean_book(E_CODE_CLEAN | E_CODE_RESET, NULL);
}
