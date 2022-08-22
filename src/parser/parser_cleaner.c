#include <stdlib.h>
#include <unistd.h>

#include "libft/ft_lst.h"
#include "libftmlx/ftmlx_color.h"

#include "fdf.h"

void clean_fd_map(enum e_code_clean code, int fd_map)
{
	static int p_fd_map = -1;

	if (code & E_CODE_INIT)
		p_fd_map = fd_map;
	if (code & E_CODE_CLEAN && p_fd_map >= 0)
	{
		close(p_fd_map);
		p_fd_map = -1;
	}
}

void clean_book(int code, t_list **entry)
{
	static t_list **p_entry = NULL;

	if (code & E_CODE_INIT)
		p_entry = entry;
	if (code & E_CODE_CLEAN && p_entry)
	{
		ft_lstclear(p_entry, free);
		*p_entry = NULL;
	}
	if (code & E_CODE_RESET)
		p_entry = NULL;
}

void exit_clean_parser()
{
	clean_fd_map(E_CODE_CLEAN, -1);
	clean_book(E_CODE_CLEAN, NULL);

	exit_clean(1, "LALAL");
}
