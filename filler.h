#ifndef FILLER_H
# define FILLER_H

#include "libft.h"

typedef struct s_filler_map
{
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
void t_map_copy(t_map *dst, t_map *src);
void t_map_del(t_map *m);
int t_map_score(t_map *m);

#endif
