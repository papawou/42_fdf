#include "fdf.h"

void setup_cam(t_scene *sc)
{
	sc->wh = (t_vec2){300, 200};
	sc->cam = (t_transform){euler_to_quat((t_euler){-35.264, 45, 0}),
													{0, 0, 0}};
	sc->cam = transform_mult_vec(sc->cam, (t_vec3){0, 0, 10});
	//sc->cam = (t_transform){euler_to_quat((t_euler){0, 0, 0}),
		//											{1, 0, 30}};
	//// sc->proj = create_orth_cam(sc->wh.x, sc->wh.y, 1000, 0, sc->cam);
	sc->proj = create_persp_cam(90.0, sc->wh.x / sc->wh.y, 1.0, 500, sc->cam);
}

int check_vertex_ndc(t_vec4 v)
{
	return (-v.w < v.x && v.x < v.w && -v.w < v.y && v.y < v.w && -v.w < v.z && v.z < v.w);
}

t_vec4 get_vertex_ndc(t_vec4 v, t_scene *sc)
{
	t_vec4 dst = mat_mult_vec(sc->proj, v);
	return dst;
}

t_vec2 ndc_to_screen(t_vec4 v, t_scene *sc)
{
	v.x /= v.w;
	v.y /= v.w;
	v.z /= v.w;
	v.w /= v.w;
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

	return mat_mult(mat_persp, transform_to_mat(transform_inv(cam)));
}

t_mat4 create_persp_cam(float fovx, float aspect, float far, float near, t_transform cam)
{
	t_mat4 mat_persp;
	mat_persp = (t_mat4){MAT4_ID};

	mat_persp.m[0][0] = 1 / (tan(deg_to_rad(fovx / 2)));
	mat_persp.m[1][1] = aspect / tan(deg_to_rad(fovx / 2));
	mat_persp.m[2][2] = -(far + near) / (far - near);
	mat_persp.m[2][3] = -(2 * (near * far)) / (far - near);
	mat_persp.m[3][2] = -1;

	return mat_mult(mat_persp, transform_to_mat(transform_inv(cam)));
}