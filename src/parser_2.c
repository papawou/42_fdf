/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 04:22:47 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/17 05:50:58 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	hex2tochar(unsigned char l, unsigned char r)
{
	unsigned char	c;

	c = 0;
	if (l <= '9')
		c |= (l - '0') << 4;
	else
		c |= (ft_tolower(l) - 'a' + 9) << 4;
	if (r <= '9')
		c |= (r - '0');
	else
		c |= (ft_tolower(r) - 'a' + 9);
	return (c);
}

int	parse_color(char *s, t_color *c)
{
	int	j;

	j = 0;
	if (s[j] == ',' && s[j + 1] == '0' && s[j + 2] == 'x')
		j += 3;
	else
		return (j);
	if (ft_isspace(s[j]))
		return (j);
	c->r = hex2tochar(s[j], s[j + 1]);
	j += 2;
	if (ft_isspace(s[j]))
		return (j);
	c->g = hex2tochar(s[j], s[j + 1]);
	j += 2;
	if (ft_isspace(s[j]))
		return (j);
	c->b = hex2tochar(s[j], s[j + 1]);
	j += 2;
	if (ft_isspace(s[j]))
		return (j);
	c->a = hex2tochar(s[j], s[j + 1]);
	j += 2;
	return (j);
}

void	parse_line(char *s, int dst[], t_color map_color[])
{
	int	i;
	int	j;

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
		j += parse_color(s + j, map_color + i);
		while (ft_isspace(s[j]))
			++j;
		++i;
	}
}