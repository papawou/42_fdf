/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:10:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/08/17 08:25:31 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_sc(t_scene *sc)
{
	sc->ft.mlx = NULL;
	sc->ft.win = NULL;
	sc->map = NULL;
	sc->map_color = NULL;
	sc->depth_buffer = NULL;
	sc->canvas = NULL;
	clean_exit(0, sc);
}
