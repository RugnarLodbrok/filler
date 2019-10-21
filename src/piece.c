#include "filler.h"

static int row_empty(char *row)
{
	while (*row)
		if (*row++ != CELL_EMPTY)
			return (0);
	return (1);
}

static int col_empty(char **col, int j)
{
	while (*col)
		if (*(*col++ + j) != CELL_EMPTY)
			return (0);
	return (1);
}

void t_map_trim(t_map *piece)
{
	int i;

	while (piece->n && col_empty(piece->data, 0))
	{
		piece->offset.y++;
		piece->n--;
		i = -1;
		while (++i < piece->m)
			piece->data[i]++;
	}
	while (piece->m && row_empty(piece->data[0]))
	{
		piece->data++;
		piece->offset.x++;
		piece->m--;
	}
	while (piece->m && row_empty(piece->data[piece->m - 1]))
		piece->m--;
	while (piece->n && col_empty(piece->data, piece->n - 1))
		piece->n--;
}
