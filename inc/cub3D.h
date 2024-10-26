#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdio.h>

# define GAME_CONF_EXT ".cub"

typedef enum e_err
{
	OK = 0,
	ERR = -1
}	t_err;

typedef struct s_tex
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
}	t_tex;

typedef union u_color
{
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	};
	unsigned int	value;
}	t_color;

typedef	struct s_conf
{
	char	**map;
	t_tex	tex;
}	t_conf;

typedef struct s_game
{
	t_conf	conf;
}	t_game;

// err.c
t_err	perr(const char *owner, const char *msg);

// file.c
bool	is_valid_ext(const char *path, const char *ext);

#endif
