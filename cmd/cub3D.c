#include <stdio.h>
#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_err	err;

	if (ac != 2)
		return (perr(__func__, "invalid argument"), 1);
	game = &(t_game){0};
	(void)av;
	printf("OK");
}
