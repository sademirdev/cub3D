#include "cub3D.h"
#include <fcntl.h>
#include <stdlib.h>

static void	conf_line_data_dispose(void	*data)
{
	if (!data)
		return ;
	free(data);
}

void	conf_line_data_dispose_noop(void *data)
{
	(void)data;
}

t_list	*conf_line_read(const char *path)
{
	t_list	*conf_line;
	t_list	*tmp;
	char	*line;
	int		fd;

	conf_line = NULL;
	if (!path)
		return (perr(__func__, "'game' or 'path' cannot be null"), NULL);
	if (!is_valid_ext(path, GAME_CONF_EXT))
		return (perr(__func__, "extension should be '.cub'"), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perr(__func__, "map file cannot be opened"), NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), perr(__func__, "empty or invalid file"), NULL);
	while (line)
	{
		tmp = ft_lstnew(line);
		if (!tmp)
			return (close(fd), ft_lstclear(&conf_line, conf_line_data_dispose), perr(__func__, "conf_line cannot be allocated"), NULL);
		ft_lstadd_back(&conf_line, tmp);
		line = get_next_line(fd);
	}
	return (close(fd), conf_line);
}

char	**conf_line_to_arr(t_list *conf_line)
{
	t_list	*tmp;
	char	**arr;
	size_t	i;

	if (!conf_line)
		return (perr(__func__, "'conf_line' cannot be null"), NULL);
	arr = (char **) malloc(sizeof(char *) * (ft_lstsize(conf_line) + 1));
	if (!arr)
		return (perr(__func__, "conf line arr cannot be allocated"), NULL);
	i = 0;
	tmp = conf_line;
	while (tmp)
	{
		arr[i] = (char *) tmp->content;
		tmp = tmp->next;
		i++;
	}
	return (arr);
}
