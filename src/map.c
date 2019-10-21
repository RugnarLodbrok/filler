#include "filler.h"

void t_map_copy(t_map *dst, t_map *src)
{
	int i;

	dst->m = src->m;
	dst->n = src->n;
	dst->data = malloc(sizeof(char *) * (dst->m + 1));
	i = 0;
	while (i < dst->m)
	{
		dst->data[i] = ft_strdup(src->data[i]);
		i++;
	}
}

int t_map_can_place(t_map *map, t_map *piece, t_point p)
{
	int i;
	int j;
	int overlap_cnt;

	overlap_cnt = 0;
	for (i = 0; i < piece->m; ++i)
	{
		for (j = 0; j < piece->n; ++j)
		{
			if (piece->data[i][j] == CELL_EMPTY)
				continue;
			if (map->data[p.x + i][p.y + j] == CELL_O)
				return (0);
			else if (overlap_cnt++)
				return (0);
		}
	}
	return (overlap_cnt == 1);
}

void t_map_place(t_map *map, t_map *piece, t_point p)
{
	int i;
	int j;

	for (i = 0; i < piece->m; ++i)
	{
		for (j = 0; j < piece->n; ++j)
		{
			if (piece->data[i][j] == CELL_EMPTY)
				continue;
			map->data[p.x + i][p.y + j] = CELL_X;
		}
	}
}

void t_map_del(t_map *m)
{
	int i;

	i = -m->offset.x;
	while (m->data[i])
	{
		free(m->data[i] - m->offset.y);
		i++;
	}
}
