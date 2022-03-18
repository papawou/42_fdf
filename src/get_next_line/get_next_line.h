#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <sys/types.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

typedef struct s_page
{
	char					buf[BUFFER_SIZE + 1];
	struct s_page	*next;
} t_page;


char		*get_next_line(int fd);
char		*ft_strchr(const char *src, const char c);
size_t	read_book(t_page **page, const int fd);
char		*cpyn_book(char *out, size_t out_size, t_page **page);

#endif