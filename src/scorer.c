#include "libft.h"
#include "filler.h"

int t_map_cnt(t_map *m, char c)
{
	int i;
	int j;
	int r;

	r = 0;
	i = -1;
	while (++i < m->m)
	{
		j = -1;
		while (++j < m->n)
			if (m->data[i][j] == c)
				r++;
	}
	return (r);
}

void check_neighbours(const t_map *m, char c, int i, int j)
{
	char *datum;
	char cc;

	cc = (char)ft_tolower(c);
	datum = &m->data[i][j];
	if (*datum != CELL_O && *datum != CELL_X)
	{
		if (i > 0 && m->data[i - 1][j] == c)
			*datum = cc;
		else if (j > 0 && m->data[i][j - 1] == c)
			*datum = cc;
		else if (i < m->m - 1 && m->data[i + 1][j] == c)
			*datum = cc;
		else if (j < m->n - 1 && m->data[i][j + 1] == c)
			*datum = cc;
	}
}

int t_map_expand(t_map *m, char c)
{
	int i;
	int j;
	char cc;
	int cnt;

	cc = (char)ft_tolower(c);
	i = -1;
	while (++i < m->m)
	{
		j = -1;
		while (++j < m->n)
		{
			check_neighbours(m, c, i, j);
		}
	}
	cnt = t_map_cnt(m, cc);
	i = -1;
	while (++i < m->m)
	{
		j = -1;
		while (++j < m->n)
			if (m->data[i][j] == cc)
				m->data[i][j] = c;
	}
	return (cnt);
}

int t_map_score(t_map *m)
{
	(void)m;
	while (1)
	{
		if (!t_map_expand(m, CELL_O))
		{
			while (t_map_expand(m, CELL_X))
				;
			break;
		}
		if (!t_map_expand(m, CELL_X))
		{
			while (t_map_expand(m, CELL_O))
				;
			break;
		}
	}
	return (t_map_cnt(m, CELL_X) - t_map_cnt(m, CELL_O));
}
