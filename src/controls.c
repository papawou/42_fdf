#include "fdf.h"

void rotate_camera(t_quat q, t_ftcam *cam)
{
	cam->tranf = quat_mult_transform(q, cam->tranf);
	ftmlx_update_cam(cam);
}