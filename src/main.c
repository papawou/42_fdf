#include "fdf.h"

int render(t_scene *sc)
{
	fill_img(sc->canvas, (t_color){0, 0, 0, 255});
	draw_map(sc);

	ftmlx_img_set_pxl_color(sc->canvas, sc->ft.wh.x / 2, sc->ft.wh.y / 2, ftmlx_get_color_int((t_color){127, 127, 127, 0}));
	ftmlx_put_vertex(sc->ft3d, (t_vec4){0, 0, 0, 1}, (t_color){255, 255, 255, 0});
	ftmlx_draw_axis(sc->ft3d, 1.0);

	mlx_put_image_to_window(sc->ft.mlx, sc->ft.win, sc->canvas->img, 0, 0);
	return 0;
}

void setup_cam(t_scene *sc)
{
	t_transform tranf = (t_transform){euler_to_quat((t_euler){-35.264, 45, 0}),
																		{0, 0, 0}};
	tranf = transform_mult_vec(tranf, (t_vec3){0, 0, 10.0});
	float scale = 0.05;
	t_mat4 proj = ftmlx_create_orth_proj(sc->ft.wh.x * scale, sc->ft.wh.y * scale, 1000, 0);
	// t_mat4 proj = create_perspx_proj(90.0, sc->ft.wh.x / sc->ft.wh.y, 1.0, 1000);
	ftmlx_init_cam(tranf, proj, &sc->cam);
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

	init_ftmlx(300, 200, &sc.ft);
	setup_cam(&sc);
	sc.canvas = ftmlx_new_img(sc.ft.mlx, sc.ft.wh.x, sc.ft.wh.y);

	sc.ft3d = (t_ftmlx3d){&sc.ft.wh, &sc.cam.proj, sc.canvas};

	parse_map(&sc);
	render(&sc);
	mlx_loop(sc.ft.mlx);
	return 0;
}

// libftmlx
/*
typdef keyboard
close window(with *function free)

draw_line
 passing gradient

using scene as big object in ftmlx and sub struct for prroject varaibles?
*/

/*
 */