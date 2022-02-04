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
} t_scene;


#endif