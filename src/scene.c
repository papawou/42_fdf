/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 08:10:46 by kmendes           #+#    #+#             */
/*   Updated: 2022/09/03 03:23:08 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void exit_clean(int code, char *str)
{
	if (code)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd(str, 1);
	clean_scene(E_CODE_CLEAN, NULL);
	exit(code);
}

void clean_scene(int code, t_scene *sc)
{
	static t_scene *p_sc = NULL;

	if (code & E_CODE_INIT)
		p_sc = sc;

	if (code & E_CODE_CLEAN)
	{
		ft_free_malloc_cont_2d((void **)p_sc->depth_buffer);
		p_sc->depth_buffer = NULL;
		ft_free_malloc_cont_2d((void **)p_sc->map);
		p_sc->map = NULL;
		ft_free_malloc_cont_2d((void **)p_sc->map_color);
		p_sc->map_color = NULL;
		if (p_sc->ft.mlx)
		{
			if (p_sc->canvas)
				ftmlx_free_img(p_sc->ft.mlx, p_sc->canvas);
			p_sc->canvas = NULL;
			if (p_sc->ft.win)
				mlx_destroy_window(p_sc->ft.mlx, p_sc->ft.win);
			p_sc->ft.win = NULL;
		}
	}
}

void init_sc(t_scene *sc)
{
	sc->map = NULL;
	sc->map_color = NULL;
	sc->depth_buffer = NULL;
	sc->ft.mlx = NULL;
	sc->ft.win = NULL;
	sc->canvas = NULL;
	clean_scene(E_CODE_INIT, sc);
}

t_vec2 get_screen_size(t_fvec2 box)
{
	t_vec2 dst;
	dst.x = 1000;
	dst.y = 1000;
	if (box.x > box.y)
		dst.y = dst.x * (box.y / box.x);
	else if (box.x < box.y)
		dst.x = dst.y * (box.x / box.y);
	return (dst);
}

void setup_scene(t_scene *sc)
{
	t_fvec2 box;
	t_fvec2 offset;
	t_vec2 screen_size;

	setup_cam(sc);
	calc_map_box(sc, &box, &offset);
	screen_size = get_screen_size(box);

	float scaleTest = screen_size.y / box.y;
	sc->map_mat = get_map_mat(scaleTest * 0.8, offset, box);
	fps_move_camera((t_fvec3) {-(offset.x * (scaleTest * 0.8) + screen_size.x * 0.1),
		(offset.y * (scaleTest * 0.8) + screen_size.y * 0.1), 0},
		&sc->cam);
	ftmlx_update_cam(&sc->cam);

	if (ftmlx_init(screen_size.x, screen_size.y, &sc->ft))
		exit_clean(1, "ftmlx failed");
	sc->depth_buffer = (float **)ft_malloc_cont_2d(sc->ft.wh.y, sc->ft.wh.x,
																								 sizeof(float));
	if (sc->depth_buffer == NULL)
		exit_clean(1, "depth_buffer failed");
	sc->canvas = ftmlx_new_img(sc->ft.mlx, sc->ft.wh.x, sc->ft.wh.y);
	if (sc->canvas == NULL)
		exit_clean(1, "canvas failed");
	sc->ft3d = (t_ftmlx3d){&sc->cam.vp, &sc->ft.wh, sc->canvas};
}