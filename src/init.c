#include "cub3D.h"
#include "libft.h"
#include <fcntl.h>

char	**read_cub_file(const char **path)
{
	char	**row_conf;
	int		fd;

	if (!path)
		return (perr(__func__, "'path' cannot be null"), NULL);
	if (!is_valid_ext(path, GAME_CONF_EXT))
		return (perr(__func__, "extension should be '.cub'"), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perr(__func__, "map file cannot be opened"));
}

t_err	game_init(t_game *game, const char *conf_path)
{
	t_err	err;

	if (!game || !conf_path)
		return (perr(__func__, "'game' or 'conf_path' cannot be null"));
	err = read_cub_file(conf_path);
	if (err)
		return (perr(__func__, "an error occurred on calling 'read_cub_file'"), ERR);

}
