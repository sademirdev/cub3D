#include "cub3d.h"
#include "libft.h"
#include <unistd.h>

t_err	perr(const char *owner, const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, "Message: ", 9);
		if (owner)
		{
			write(2, "[", 1);
			write(2, owner, ft_strlen(owner));
			write(2, "]: ", 3);
		}
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (ERR);
}

t_err	fatal(const char *owner, const char *msg)
{
	perr(owner, msg);
	exit(127);
	return (ERR);
}
