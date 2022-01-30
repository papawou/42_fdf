#include <libft/math.h>

int main()
{
	t_vec4 test = {1, 0, 0, 1};
	t_mat4 mat = {{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}
	};

	ft_mult_vec_mat(test, mat);

	return 0;
}