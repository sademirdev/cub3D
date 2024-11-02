#include "cub3D.h"

bool	strevery(int (*func)(int c),  const char *str)
{
	int	i;

	if (!func || !str)
		return (perr(__func__, "'func' or 'str' cannot be null"), false);
	i = 0;
	while (str[i])
	{
		if (!func(str[i]))
			return (false);
		i++;
	}
	return (true);
}

size_t	str_arr_len(const char **arr)
{
	size_t	i;

	if (!arr)
		return (perr(__func__, "'arr' cannot be null"), 0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	str_arr_dispose(char ***arr_ptr)
{
	size_t	i;

	if (!arr_ptr || !*arr_ptr)
		return ;
	i = 0;
	while ((*arr_ptr)[i])
	{
		free((*arr_ptr)[i]);
		(*arr_ptr)[i] = NULL;
		i++;
	}
	free(*arr_ptr);
	*arr_ptr = NULL;
}

bool	is_empty_space_exc_ln(const char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}
