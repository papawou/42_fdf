#ifndef LIB_UTILS_H
#define LIB_UTILS_H

#include <libftmlx.h>

//libft_utils
t_fvec3 tri_point_bar(t_vec2 a, t_vec2 b, t_vec2 c, t_vec2 point);
float barerp(float a, float b, float c, t_fvec3 w);
t_color color_barerp(t_color a, t_color b, t_color c, t_fvec3 w);
float fvec3_dot(t_fvec3 a, t_fvec3 b);
t_fvec3	fvec3_cross(t_fvec3 a, t_fvec3 b);

//shder_map_triangle.c
int shader_map_triangle(t_fvec4 a, t_fvec4 b, t_fvec4 c, t_scene *sc);

#endif