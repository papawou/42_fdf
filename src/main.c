#include "fdf.h"

int render(t_scene *sc)
{
	reset_img(sc->canvas);
	draw_map(sc);
	//print_axis(sc);
	ftmlx_img_set_pxl_color(sc->canvas, sc->wh.x / 2, sc->wh.y / 2, ftmlx_get_color_int((t_color){127, 127, 127, 0}));
	put_vertex((t_vec4){0, 0, 0, 1}, (t_color){0, 255, 0, 0}, sc);

	mlx_put_image_to_window(sc->mlx, sc->win, sc->canvas->img, 0, 0);
	return 0;
}

int parse_map(t_scene *sc)
{
	sc->map_size.y = 2;
	sc->map_size.x = 3;

	sc->tr_map.q = (t_quat)QUAT_ID;
	sc->tr_map.v = (t_vec3){0, 0, 0};
	sc->map = (int **)ft_malloc_cont_2d(sc->map_size.y, sc->map_size.x, sizeof(int));

	sc->map[0][0] = 5;
	sc->map[0][1] = 4;
	sc->map[0][2] = 3;
	sc->map[1][0] = 2;
	sc->map[1][1] = 1;
	sc->map[1][2] = 0;

	return 0;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_scene sc;

	setup_cam(&sc);
	parse_map(&sc);
	sc.mlx = mlx_init();
	if (sc.mlx == NULL)
	{
		ft_putstr_fd("MLX_INIT() RETURN NULL", 1);
		return 1;
	}
	sc.win = mlx_new_window(sc.mlx, sc.wh.x, sc.wh.y, "fdf");
	sc.canvas = ftmlx_new_img(sc.mlx, sc.wh.x, sc.wh.y);

	render(&sc);
	mlx_loop(sc.mlx);
	return 0;
}