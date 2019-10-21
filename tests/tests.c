#include "filler.h"

void t_piece_print(t_map *p)
{
	int i;
	int j;

	for (i = 0; i < p->m; i++)
	{
		for (j = 0; j < p->n; j++)
		{
			write(1, p->data[i] + j, 1);
		}
		write(1, "\n", 1);
	}
}

int main()
{
	t_map piece;

	ft_bzero(&piece, sizeof(piece));
	piece.data = malloc(sizeof(char *) * 6);
	piece.m = 5;
	piece.n = 7;
	piece.data[0] = ft_strdup(".......");
	piece.data[1] = ft_strdup("..*....");
	piece.data[2] = ft_strdup("..*....");
	piece.data[3] = ft_strdup("..***..");
	piece.data[4] = ft_strdup(".......");
	piece.data[5] = 0;
	t_piece_print(&piece);
	t_map_trim(&piece);
	t_piece_print(&piece);
	t_map_del(&piece);
}
