#include "cub3D.h"

static t_err	conf_meta_validate_element_count(const t_conf_meta *meta)
{
	if (!meta)
		return (perr(__func__, "'count' cannot be null"));
	if (meta->no != 1 || meta->so != 1 || meta->we != 1 || meta->ea != 1 || meta->f != 1 || meta->c != 1)
		return (perr(__func__, "invalid element count"));
	return (OK);
}

t_err	conf_init(t_game *game, char **line_arr)
{
	t_conf_meta	meta;
	t_scalar	map_sca;
	size_t		i;
	t_err		err;

	if (!game || !line_arr)
		return (perr(__func__, "'game' or 'path' or 'map_sca values' cannot be null or zero"));
	meta = (t_conf_meta){0};
	map_sca = map_sca_calculate(line_arr);
	if (!map_sca.h && !map_sca.w)
		return (perr(__func__, "an error occurred on calling 'map_sca_calculate'"));
	i = 0;
	while (line_arr[i])
	{
		if (map_is_first_line(line_arr[i]))
			break ;
		err = elements_read(game, line_arr[i], &meta);
		if (err)
			return (err);
		i++;
	}
	err = map_read(game, line_arr, i, map_sca);
	if (err)
		return (err);
	return (conf_meta_validate_element_count(&meta));
}
