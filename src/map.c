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
	(void)map;
	(void)piece;
	(void)p;
	return (1);
}

void t_map_place(t_map *map, t_map *piece, t_point p)
{
	(void)map;
	(void)piece;
	(void)p;
}

int t_map_score(t_map *m)
{
	(void)m;
	return (0);
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
