/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:24 by kmendes           #+#    #+#             */
/*   Updated: 2022/05/31 04:31:24 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdlib.h>
#include "libs/get_next_line.h"

static void	fill_buff(char *buf, char *cursor)
{
	size_t	i;

	i = 0;
	while (cursor && cursor[i])
	{
		buf[i] = cursor[i];
		++i;
	}
	buf[i] = 0;
}

static char	*gen_out(char *buf, t_page *entry_page, size_t out_size)
{
	char		*cursor_page;
	char		*out;
	size_t	i;

	if (out_size < 1)
		return (NULL);
	out = malloc(out_size + 1);
	if (out == NULL)
		return (NULL);
	out[out_size] = 0;
	i = 0;
	while (buf[i] && i < out_size)
	{
		out[i] = buf[i];
		++i;
	}
	if (entry_page)
	{
		cursor_page = cpyn_book(out + i, out_size - i, &entry_page);
		fill_buff(buf, cursor_page);
		free(entry_page);
	}
	else
		fill_buff(buf, buf + i);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "";
	t_page			*entry_page;
	char				*buf_cursor;
	size_t			size_test;

	if (fd < 0)
		return (NULL);
	entry_page = NULL;
	buf_cursor = ft_strchr(buf, '\n');
	if (*buf_cursor != '\n')
	{
		size_test = read_book(&entry_page, fd);
		return (gen_out(buf, entry_page, (buf_cursor - buf) + size_test));
	}
	else if (*buf_cursor)
		return (gen_out(buf, entry_page, buf_cursor - buf + 1));
	else
		return (NULL);
}

/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("./test", O_RDONLY);

	char *s;
	s = get_next_line(fd);
	while(s)
	{
		printf("%s", s);
		s = get_next_line(fd);
	}
	return 0;
}
*/