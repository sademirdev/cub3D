#include "cub3D.h"
#include "libft.h"

bool	is_valid_ext(const char *path, const char *ext)
{
	size_t	len;

	if (!path || !ext)
		return (false);
	len = ft_strlen(ext);
	if (ft_strlen(path) < len
		|| ft_strncmp(ext, path + (ft_strlen(path) - len), len))
		return (false);
	return (true);
}
