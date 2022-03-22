#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "libs/get_next_line.h"

char	*ft_strchr(const char *src, const char c)
{
	while (*src)
	{
		if (*src == c)
			return (char *) src;
		++src;
	}
	return (char *) src;
}

size_t gen_page(t_page **page, const int fd)
{
	ssize_t readed_bytes;

//init
	*page = malloc(sizeof(t_page));
	if (*page == NULL)
		return 0;
	(*page)->buf[BUFFER_SIZE] = 0;
	(*page)->next = NULL;
	readed_bytes = read(fd, (*page)->buf, BUFFER_SIZE);
	if (readed_bytes < 1)
	{
		free(*page);
		*page = NULL;
	}
	else
		(*page)->buf[readed_bytes] = 0;
	return (readed_bytes);
}

size_t	read_book(t_page **page, const int fd)
{
	size_t	out_size;
	t_page 	*tmp_page;
	char		*n_pos;
	ssize_t	readed_bytes;
	
	out_size = 0;
	readed_bytes = gen_page(page, fd);
	if (readed_bytes < 1)
		return (0);
	out_size += readed_bytes;
	tmp_page = *page;
	while (1)
	{
		n_pos = ft_strchr(tmp_page->buf, '\n');
		if (*n_pos == '\n')
			return out_size - ((tmp_page->buf + readed_bytes) - n_pos) + 1;
		readed_bytes = gen_page(&tmp_page->next, fd);
		if (readed_bytes < 1)
			return (out_size);
		out_size += readed_bytes;
		tmp_page = tmp_page->next;
	}
}

char *cpyn_book(char *out, size_t out_size, t_page **page)
{
	t_page	*tmp_page;
	size_t	i;

	i = 0;
	while (out_size--)
	{
		if ((*page)->buf[i] == 0)
		{
			i = 0;
			tmp_page = *page;
			*page = (*page)->next;
			free(tmp_page);
		}
		*out = (*page)->buf[i++];
		++out;
	}
	return (*page)->buf + i;
}