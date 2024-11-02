#include <stdio.h>
#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_err	err;

	if (ac != 2)
		return (perr(__func__, "invalid argument"), 1);
	game = &(t_game){};
	game->conf.match = (t_dir_str_data){
		.data = {
			[NO] = NO_STR,
			[SO] = SO_STR,
			[WE] = WE_STR,
			[EA] = EA_STR,
			[F] = F_STR,
			[C] = C_STR,
		}
	};
	err = game_init(game, av[1]);
	if (err)
		return (game_dispose(game), 2);
}
