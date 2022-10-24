/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:12:53 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/29 14:12:53 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_clamp(float min, float max, float value)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	ft_lerp(float start, float end, float alpha)
{
	return ((1 - alpha) * start + alpha * end);
}

float	ft_invlerp(float start, float end, float value)
{
	return ((value - start) / (end - start));
}

typedef struct s_remap_p
{
	float	input_a;
	float	input_b;
	float	out_a;
	float	out_b;
}	t_remap_p;

float	ft_remap(t_remap_p p, float value)
{
	return (ft_lerp(p.out_a, p.out_b, ft_invlerp(p.input_a, p.input_b, value)));
}
