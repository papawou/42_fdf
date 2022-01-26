#ifndef MAT_H
#define MAT_H

typedef struct s_vec2
{
	float x;
	float y;
} t_vec2;

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

typedef struct s_vec4
{
	float x;
	float y;
	float z;
	float w;
} t_vec4;

typedef struct s_mat4
{
	float m[4][4];
} t_mat4;

t_vec4 mult_vec_mat(t_vec4 v, const t_mat4 m);

#endif