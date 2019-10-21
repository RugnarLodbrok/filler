#ifndef FILLER_H
# define FILLER_H

#include "libft.h"

#define CELL_EMPTY '.'
#define CELL_FULL '*'
#define CELL_X 'X'
#define CELL_O 'O'

typedef struct s_filler_map
{
	t_point offset;
	int m;
	int n;
	char **data;
} t_map;

typedef struct
{
	char turn;
	t_map map;
	t_map piece;
} t_game_state;

t_map t_map_read(int fd, char *name, int skip_margin);
int t_map_can_place(t_map *map, t_map *piece, t_point p);
void t_map_place(t_map *map, t_map *piece, t_point p);
void t_map_copy(t_map *dst, t_map *src);
void t_map_del(t_map *m);
int t_map_score(t_map *m);
void t_map_flip_xo(t_map *m);
void t_map_trim(t_map *piece);

#endif
