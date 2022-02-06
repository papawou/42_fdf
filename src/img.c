#include "fdf.h"

void reset_img(t_img *img)
{
	int x;
	int y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ftmlx_img_set_pxl_color(img, x, y, ftmlx_get_color_int((t_color){0, 0, 0, 0}));
			++x;
		}
		++y;
	}
}
