#include "fdf.h"

void setup_cam(t_scene *sc)
{
	sc->wh = (t_vec2){300, 200};
	sc->cam = (t_transform){euler_to_quat((t_euler){0, 0, 0}),
													{0, 0, 100}};
	sc->proj = create_orth_cam(sc->wh.x, sc->wh.y, 1000, 0, sc->cam);
}

int check_vertex_ndc(t_vec4 v)
{
	return (-1.0 < v.x && v.x < 1.0 && -1.0 < v.y && v.y < 1.0 && -1.0 < v.z && v.z < 1.0);
}

t_vec4 get_vertex_ndc(t_vec4 v, t_scene *sc)
{
	return mat_mult_vec(sc->proj, v);
}

t_vec2 ndc_to_screen(t_vec4 v, t_scene *sc)
{
	return (t_vec2){ft_remap(-1.0, 1.0, 0, sc->wh.x, v.x), ft_remap(1.0, -1.0, 0, sc->wh.y, v.y)};
}

t_mat4 create_orth_cam(float width, float height, float far, float near, t_transform cam)
{
	float scale = 0.05;
	t_mat4 mat_persp;
	mat_persp = (t_mat4){MAT4_ID};
	mat_persp.m[0][0] = 2 / (width * scale);
	mat_persp.m[1][1] = 2 / (height * scale);
	mat_persp.m[2][2] = -2 / (far - near);
	mat_persp.m[2][3] = -(far + near) / (far - near);

	return mat_mult_mat(mat_persp, transform_to_mat(transform_inv(cam)));
}