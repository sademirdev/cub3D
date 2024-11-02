#include "cub3D.h"

static t_err	tex_check_line_count(size_t *count)
{
	(*count)++;
	if (*count > 1)
		return (perr(__func__, "invalid element count"));
	return (OK);
}

static t_err	tex_set_value(char **tex, const char *line)
{
	char	*buf;

	if (!line || !tex)
		return (perr(__func__, "'line' or 'tex' cannot be null"));
	buf = ft_strtrim(line, SPACES);
	if (!buf)
		return (perr(__func__, "buf cannot be allocated on calling ft_strtrim"));
	*tex = ft_strjoin(buf, GAME_CONF_EXT);
	if (!*tex)
		return (free(buf), perr(__func__, "tex cannot be allocated on calling ft_strjoin"));
	free(buf);
	return (OK);
}

static t_err	color_set_value(t_color *color, const char *line)
{
	char	**rgb_str;
	char	*buf;

	if (!color || !line)
		return (perr(__func__, "'color' or 'line' cannot be null"));
	buf = ft_strtrim(line, SPACES);
	if (!buf)
		return (perr(__func__, "buf cannot be allocated on calling ft_strtrim"));
	rgb_str = ft_split(buf, ',');
	if (!rgb_str)
		return (perr(__func__, "rgb_str cannot be allocated on calling ft_split"));
	if (str_arr_len((const char **) rgb_str) != 3)
		return (perr(__func__, "invalid rgb_str len"));
	if (!strevery(ft_isdigit, rgb_str[0]) || !strevery(ft_isdigit, rgb_str[1]) || !strevery(ft_isdigit, rgb_str[2]))
		return (perr(__func__, "rgb_str cannot have non digit character"));
	color->red = ft_atoi(rgb_str[0]);
	color->green = ft_atoi(rgb_str[1]);
	color->blue = ft_atoi(rgb_str[2]);
	if (color->red > 255 || color->red > 255 || color->green > 255 || \
		color->green < 0 || color->blue < 0 || color->blue < 0)
		return (perr(__func__, "rgb_str has to be between 0 to 255"));
	return (OK);
}

static t_err	elements_set(t_game *game, const char *line, t_dir_str const type)
{
	if (!game || !line || type == END)
		return (perr(__func__, "'game' or 'line' or 'type' cannot be null or END or START"));
	if (type == C || type == F)
		tex_set_value(&game->conf.grad[type], line);
	else
		tex_set_value(&game->conf.tex[type], line);
	return (OK);
}

t_err	elements_read(t_game *game, const char *line, t_conf_meta *meta)
{
	t_dir_str	_;
	char		*str;

	_ = START;
	if (!line || !meta)
		return (perr(__func__, "'line' or 'count' cannot be null"));
	while (*line || is_empty_space_exc_ln(*line))
		line++;
	while (_++ != END)
	{
		str = game->conf.match.data[_];
		if (!ft_strncmp(line, str, ft_strlen(str)))
			return (elements_set(game, line, _), tex_check_line_count(&meta->f));
	}
	return (OK);
}
