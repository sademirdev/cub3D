#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

# define GAME_CONF_EXT ".cub"
# define SPACES "\t\v\f\r\n "

# define NO_STR "NO "
# define SO_STR "SO "
# define WE_STR "WE "
# define EA_STR "EA "
# define F_STR "F "
# define C_STR "C "

typedef struct s_conf_meta
{
	unsigned char	no;
	unsigned char	so;
	unsigned char	we;
	unsigned char	ea;
	unsigned char	f;
	unsigned char	c;
}	t_conf_meta;

typedef enum e_dir_str
{
	START,
	NO,
	SO,
	WE,
	EA,
	END
}	t_dir_str;

typedef u
	F,
	C,

typedef struct s_scalar
{
	size_t	h;
	size_t	w;
}	t_scalar;

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

typedef struct s_dir_str_data
{
	char	*data[END];
}	t_dir_str_data;

typedef	struct s_conf
{
	t_dir_str_data	match;
	char			**map;
	struct
	{
		char *tex[4]: 8;
		char : 1;
	};


	char			*tex[END - (1 + 2)];
	t_color			grad[2];
}	t_conf;

typedef struct s_game
{
	t_conf	conf;
}	t_game;

// conf_line.c
void		conf_line_data_dispose_noop(void *data);
t_list		*conf_line_read(const char *path);
char		**conf_line_to_arr(t_list *conf_line);

// conf_line.c
t_err		conf_init(t_game *game, char **line_arr);

// elements.c
t_err		elements_read(t_game *game, const char *line, t_conf_meta *count);

// err.c
t_err		perr(const char *owner, const char *msg);
t_err		fatal(const char *owner, const char *msg);

// file.c
bool		is_valid_ext(const char *path, const char *ext);

// game.c
void		game_dispose(t_game *game);
t_err		game_init(t_game *game, const char *conf_path);

// map_util.c
bool		map_is_first_line(const char *line);
t_scalar	map_sca_calculate(char **line_arr);
t_err		map_read(t_game *game, char **line_arr, size_t i, t_scalar map_sca);

// str_util.c
bool		strevery(int (*func)(int c),  const char *str);
size_t		str_arr_len(const char **arr);
void		str_arr_dispose(char ***arr_ptr);
bool		is_empty_space_exc_ln(const char c);

#endif
