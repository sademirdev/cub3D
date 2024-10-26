#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdio.h>

# define GAME_CONF_EXT ".cub"
# define SPACES "\t\v\f\r\n "

# define NO "NO "
# define SO "SO "
# define WE "WE "
# define EA "EA "
# define F "F "
# define C "C "

typedef struct s_count
{
	unsigned char	no;
	unsigned char	so;
	unsigned char	we;
	unsigned char	ea;
	unsigned char	f;
	unsigned char	c;
}	t_count;

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
		unsigned char	red;
		unsigned char	green;
		unsigned char	blue;
		unsigned char	alpha;
	};
	unsigned int	value;
}	t_color;

typedef	struct s_conf
{
	char	**map;
	t_tex	tex;
	t_color	c;
	t_color	f;
}	t_conf;

typedef struct s_game
{
	t_conf	conf;
}	t_game;

// err.c
t_err	perr(const char *owner, const char *msg);
t_err	fatal(const char *owner, const char *msg);

// file.c
bool	is_valid_ext(const char *path, const char *ext);

#endif
