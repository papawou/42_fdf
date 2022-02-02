#ifndef FDF_H
#define FDF_H

#include <libft/math.h>
#include <math.h>
typedef struct s_scene
{
	t_mat4 cam;
} t_scene;


//quat.c
t_quat quat_norm(t_quat q);
t_quat quat_mult(t_quat a, t_quat b, int norm);
t_mat4 quat_to_mat(t_quat q);
t_quat quat_inv(t_quat q);

//euler.c
t_mat4 euler_to_mat(t_euler v);
t_quat euler_to_quat(t_euler v);

//axig.c
t_quat axisg_to_quat(t_axisg ag);

#endif