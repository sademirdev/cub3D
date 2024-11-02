#include "cub3D.h"

bool	map_is_first_line(const char *line)
{
	size_t	i;
	bool	has_one;

	if (!line)
		return (false);
	i = 0;
	has_one = false;
	while (line[i])
	{
		if (!is_empty_space_exc_ln(line[i]) && line[i] != '1')
			return (false);
		if (line[i] == '1')
			has_one = true;
		i++;
	}
	return (has_one);
}

t_scalar	map_sca_calculate(char **line_arr)
{
	t_scalar	map_sca;
	size_t		i;

	map_sca = (t_scalar){0};
	if (!line_arr)
		return (perr(__func__, "'line_arr' cannot be null"), map_sca);
	i = 0;
	while (line_arr[i] && !map_is_first_line(line_arr[i]))
		i++;
	if (!line_arr[map_sca.h])
		return (perr(__func__, "invalid map"), map_sca);
	map_sca.h = i;
	while (line_arr[map_sca.h])
	{
		if (line_arr[map_sca.h] && map_sca.w < ft_strlen(line_arr[map_sca.h]))
			map_sca.w = ft_strlen(line_arr[map_sca.h]);
		map_sca.h++;
	}
	map_sca.h -= i;
	return (map_sca);
}

t_err	map_read(t_game *game, char **line_arr, size_t i, t_scalar map_sca)
{
	if (!game || !line_arr)
		return (__func__, "'game' or 'line_arr' cannot be null");

}
