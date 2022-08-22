/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:33 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/01 13:33:33 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif

#include "parser.h"

typedef struct s_page
{
	char			buf[BUFFER_SIZE + 1];
	struct s_page	*next;
}	t_page;

char	*get_next_line(int fd);
char	*ft_strchr(const char *src, const char c);
size_t	read_book(t_page **page, const int fd);
char	*cpyn_book(char *out, size_t out_size, t_page **page);
void exit_clean_gnl(int code, t_page **entry);

#endif