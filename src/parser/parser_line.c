/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:22:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/16 12:19:24 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	chartohex(unsigned char c, unsigned char *dst)
{
	c = ft_tolower(c);
	if (ft_isdigit(c))
		*dst |= (c - '0');
	else if ('a' <= c && c <= 'f')
		*dst |= (c - 'a' + 10);
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
	c = (c << 4);
	if (chartohex(s[1], &c))
		return (1);
	*dst = c;
	*dst_j += 2;
	return (0);
}

static int	pre_parsercolor(char *s, t_color *dst, int j, int count)
{
	if (count == 8)
	{
		if (charto2hex(s + j, &dst->a, &j))
			return (-1);
		count -= 2;
	}
	if (count == 6)
	{
		if (charto2hex(s + j, &dst->r, &j))
			return (-1);
		count -= 2;
	}
	if (count == 4)
	{
		if (charto2hex(s + j, &dst->g, &j))
			return (-1);
		count -= 2;
	}
	if (count == 2)
	{
		if (charto2hex(s + j, &dst->b, &j))
			return (-1);
	}
	return (j);
}

static int	parsecolor(char *s, t_color *dst)
{
	int		j;
	int		count;

	j = 0;
	if (s[j] == ',' && s[j + 1] == '0' && ft_tolower(s[j + 2]) == 'x')
		j += 3;
	else
		return (j);
	*dst = (t_color){0, 0, 0, 0};
	count = 0;
	while (s[j + count] && ft_strchr("abcdefABCDEF0123456789", s[j + count]))
		++count;
	if (count % 2 || count > 8 || count == 0)
		return (-1);
	return (pre_parsercolor(s, dst, j, count));
}

int	parse_line(char *s, int dst[], t_color map_color[])
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (s[j] && s[j] != '\n')
	{
		tmp = ft_atoi_safe(s + j, dst + i);
		if (tmp == -1)
			return (1);
		j += tmp;
		map_color[i] = (t_color){255, 255, 255, 0};
		tmp = parsecolor(s + j, map_color + i);
		if (tmp == -1)
			return (1);
		j += tmp;
		if (s[j] && !ft_isspace(s[j]))
			return (1);
		while (ft_isspace(s[j]))
			++j;
		++i;
	}
	return (0);
}
