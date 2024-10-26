#include "cub3D.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

static size_t	calculate_map_len(const char **path)
{
	char	*line;
	int		fd;
	size_t	len;

	if (!path)
		return (fatal(__func__, "'path' cannot be null"), NULL);
	if (!is_valid_ext(path, GAME_CONF_EXT))
		return (fatal(__func__, "extension should be '.cub'"), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (fatal(__func__, "map file cannot be opened"));
	line = get_next_line(fd);
	if (!line)
		return (close(fd), fatal(__func__, "empty or invalid file"));
	len = 0;
	while (line)
	{
		if (len < ft_strlen(line))
			len = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), len);
}

static bool	is_empty_space(const char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

static t_err	check_tex_line_count(size_t *count)
{
	(*count)++;
	if (*count > 1)
		return (perr(__func__, "invalid element count"));
	return (OK);
}

static t_err	set_tex_value(char **tex, const char *line)
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

static bool	strevery(int (*func)(int c),  const char *str)
{
	int	i;

	if (!func || !str)
		return (perr(__func__, "rgb_str cannot be null"), false);
	i = 0;
	while (str[i])
	{
		if (!func(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static size_t	arr_len(const unsigned char **arr)
{
	size_t	i;

	if (!arr)
		return (perr(__func__, "'arr' cannot be null"), 0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static t_err	set_color_value(t_color *color, const char *line)
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
	if (arr_len(rgb_str) != 3)
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

static t_err	set_elements(t_game *game, const char *line, const char *type)
{
	if (!game || !line || !type)
		return (perr(__func__, "'game' or 'line' or 'type' cannot be null"));
	if (type == NO)
		set_tex_value(&game->conf.tex.n, line);
	if (type == SO)
		set_tex_value(&game->conf.tex.s, line);
	if (type == WE)
		set_tex_value(&game->conf.tex.w, line);
	if (type == EA)
		set_tex_value(&game->conf.tex.e, line);
	if (type == F)
		set_color_value(&game->conf.c, line);
	if (type == C)
		set_color_value(&game->conf.f, line);
	return (OK);
}

static t_err	read_elements(t_game *game, const char *line, t_count *count)
{
	if (!line || !count)
		return (perr(__func__, "'line' or 'count' cannot be null"));
	while (*line || is_empty_space(*line))
		line++;
	if (ft_strncmp(line, NO, 3) == 0)
		return (set_elements(game, line, NO), check_tex_line_count(&count->no));
	if (ft_strncmp(line, SO, 3) == 0)
		return (set_elements(game, line, SO), check_tex_line_count(&count->so));
	if (ft_strncmp(line, WE, 3) == 0)
		return (set_elements(game, line, WE), check_tex_line_count(&count->we));
	if (ft_strncmp(line, EA, 3) == 0)
		return (set_elements(game, line, EA), check_tex_line_count(&count->ea));
	if (ft_strncmp(line, F, 2) == 0)
		return (set_elements(game, line, F), check_tex_line_count(&count->f));
	if (ft_strncmp(line, C, 2) == 0)
		return (set_elements(game, line, C), check_tex_line_count(&count->c));
	return (OK);
}

static t_err	process_line(t_game *game, const char *line, t_count *count)
{
	t_err	err;

	if (!line)
		return (perr(__func__, "'line' cannot be null"));
	err = read_elements(game, line, count);
	if (err)
		return (err);
	return (OK);
}

static t_err	is_valid_element_count(const t_count *count)
{
	if (!count)
		return (perr(__func__, "'count' cannot be null"));
	if (count->no == 0 || count->so == 0 || count->we == 0 || count->ea == 0 || count->f == 0 || count->c == 0)
		return (perr(__func__, "invalid element count"));
	return (OK);
}

static t_err	conf_init(t_game *game, size_t size, const char *path)
{
	static	t_count count;
	char	*line;
	int		fd;
	t_err	err;

	if (!game || !path)
		return (perr(__func__, "'game' or 'path' cannot be null"));
	if (!is_valid_ext(path, GAME_CONF_EXT))
		return (fatal(__func__, "extension should be '.cub'"), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (fatal(__func__, "map file cannot be opened"));
	line = get_next_line(fd);
	if (!line)
		return (close(fd), fatal(__func__, "empty or invalid file"));
	while (line)
	{
		err = process_line(game, line, &count);
		if (err)
			return (free(line), close(fd), ERR);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), is_valid_element_count(&count));
}

t_err	game_init(t_game *game, const char *conf_path)
{
	size_t	max_len;
	t_err	err;

	if (!game || !conf_path)
		return (perr(__func__, "'game' or 'conf_path' cannot be null"));
	max_len = calculate_map_len(conf_path);
	err = conf_init(game, max_len, conf_path);
	if (err)
		return (perr(__func__, "an error occurred on calling 'conf_init'"));
	return (OK);
}
