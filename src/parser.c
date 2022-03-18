#include <fcntl.h>
#include "fdf.h"
void parse_line(char *s, int dst[])
{
	int i = 0;
	while (*s)
	{
		s = custom_atoi(s, dst + i);
		++i;
	}
}

int parse_map(char *map_path, t_scene *sc)
{
	char *line;
	int fd_map;
	int i;
	// sc->tr_map.q = (t_quat)QUAT_ID;
	// sc->tr_map.v = (t_fvec3){0, 0, 0};

	fd_map = open(map_path, O_RDONLY);
	line = get_next_line(fd_map);
	sc->map_size.x = ft_strlen(line);
	i = 0;
	while (line)
	{
		free(line);
		get_next_line(fd_map);
		++i;
	}
	sc->map_size.y = i;
	sc->map = (int **) malloc(sizeof(int *) * sc->map_size.y);
	line = get_next_line(fd_map); // reopen?
	i = 0;
	while (line)
	{
		sc->map[i] = (int *)malloc(sc->map_size.x * sizeof(int));
		parse_line(line, sc->map[i]);
		++i;
		line = get_next_line(fd_map);
	}
	return 0;
}