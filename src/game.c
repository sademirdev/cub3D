#include "cub3D.h"

void	game_dispose(t_game *game)
{
	if (!game)
		return ;
	free(game->conf.tex.e);
	game->conf.tex.e = NULL;
	free(game->conf.tex.n);
	game->conf.tex.n = NULL;
	free(game->conf.tex.s);
	game->conf.tex.s = NULL;
	free(game->conf.tex.w);
	game->conf.tex.w = NULL;
	str_arr_dispose(game->conf.map);
}

t_err	game_init(t_game *game, const char *conf_path)
{
	t_list		*conf_line;
	char		**line_arr;
	t_err		err;

	if (!game || !conf_path)
		return (perr(__func__, "'game' or 'conf_path' cannot be null"));
	conf_line = conf_line_read(conf_path);
	if (!conf_line)
		return (perr(__func__, "an error occurred on calling 'conf_line_read'"));
	line_arr = conf_line_to_arr(conf_line);
	ft_lstclear(&conf_line, conf_line_data_dispose_noop);
	if (!line_arr)
		return (str_arr_dispose(&line_arr), perr(__func__, "an error occurred on calling 'conf_line_to_arr'"));
	err = conf_init(game, line_arr);
	if (err)
		return (str_arr_dispose(&line_arr), perr(__func__, "an error occurred on calling 'conf_init'"));
	return (OK);
}
