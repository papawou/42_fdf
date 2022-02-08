#ifndef FDF_H
#define FDF_H

#include <libft.h>
#include <libftmlx.h>
#include <math.h>

typedef struct s_scene
{
	t_mlx mlx;
	t_mlx_win win;
	t_img *canvas;

	t_transform cam;
	t_mat4 proj;
	t_vec2 wh;

	t_transform tr_map;
	int **map;
	t_vec2 map_size;
} t_scene;

// cam
void put_vertex(t_vec4 v, t_color c, t_scene *sc);
int check_vertex_ndc(t_vec4 v);
t_vec4 get_vertex_ndc(t_vec4 v, t_scene *sc);
t_vec2 ndc_to_screen(t_vec4 v, t_scene *sc);
t_mat4 create_orth_cam(float width, float height, float far, float near, t_transform cam);
t_mat4 create_persp_cam(float fovx, float aspect, float far, float near, t_transform cam);
void setup_cam(t_scene *sc);
// img
void reset_img(t_img *img);

// draw
void draw_line(t_vec2 a, t_vec2 b, t_color c, t_scene *sc);
void draw_face(t_vec4 a, t_vec4 b, t_scene *sc);
void draw_column(t_vec4 org, t_scene *sc);
void print_axis(t_scene *sc);
void draw_map(t_scene *sc);
void put_vertex(t_vec4 v, t_color c, t_scene *sc);
#endif