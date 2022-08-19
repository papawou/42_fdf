/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:22:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/19 15:47:49 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	chartohex(unsigned char c, unsigned char *dst)
{
	c = ft_tolower(c);
	if (ft_isdigit(c))
		*dst |= (c - '0');
	else if ('a' <= c && c <= 'f')
		*dst |= (c - 'a' + 9);
	else
		return (1);
	return (0);
}

static int	charto2hex(char *s, unsigned char *dst, int *dst_j)
{
	unsigned char	c;

	c = 0;
	if (!s[0] && !s[1])
		return (1);
	if (chartohex(s[0], &c))
		return (1);
	c |= c << 4;
	if (chartohex(s[1], &c))
		return (1);
	*dst = c;
	*dst_j += 2;
	return (0);
}

static int	parsecolor(char *s, t_color *dst)
{
	int		j;

	j = 0;
	if (s[j] == ',' && s[j + 1] == '0' && ft_tolower(s[j + 2]) == 'x')
		j += 3;
	else
		return (j);
	if (charto2hex(s + j, &dst->r, &j))
		return (-1);
	if (ft_isspace(s[j]))
		return (j);
	if (charto2hex(s + j, &dst->g, &j))
		return (-1);
	if (ft_isspace(s[j]))
		return (j);
	if (charto2hex(s + j, &dst->b, &j))
		return (-1);
	if (ft_isspace(s[j]))
		return (j);
	if (charto2hex(s + j, &dst->a, &j))
		return (-1);
	return (j);
}

void	parse_line(char *s, int dst[], t_color map_color[])
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (s[j] && s[j] != '\n')
	{
		dst[i] = ft_atoi(s + j);
		map_color[i] = (t_color){0, 0, 0, 0};
		if (s[j] == '+' || s[j] == '-')
			++j;
		while (s[j] && ft_isdigit(s[j]))
			++j;
		tmp = parsecolor(s + j, map_color + j);
		if (tmp == -1)
			exit(EXIT_FAILURE);
		j += tmp;
		if (s[j] && !ft_isspace(s[j]))
			exit(EXIT_FAILURE);
		while (ft_isspace(s[j]))
			++j;
		++i;
	}
}
