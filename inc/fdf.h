#ifndef FDF_H
#define FDF_H

#include <libft.h>
#include <libftmlx.h>
#include <math.h>

typedef struct s_scene
{
	t_ftmlx ft;
	t_ftcam cam;
	t_ftmlx3d ft3d;
	
	t_img *canvas;

	int **map;
	t_transform tr_map;
	t_vec2 map_size;
} t_scene;

// draw
void draw_map(t_scene *sc);
void draw_face(t_vec4 a, t_vec4 b, t_scene *sc);
void draw_column(t_vec4 org, t_scene *sc);
void setup_cam(t_scene *sc);
#endif