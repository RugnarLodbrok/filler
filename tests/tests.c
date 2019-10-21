#include <fcntl.h>
#include "libft_compat.h"
#include "filler.h"

int t_map_expand(t_map *m, char c);
t_map t_map_read(int fd, char *name, int skip_margin);

void t_map_print(t_map *p)
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
	write(1, "\n", 1);
}

int test_piece_trim()
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
	t_map_print(&piece);
	t_map_trim(&piece);
	t_map_print(&piece);
	t_map_del(&piece);
}

int test_expand()
{
	t_map m;
	int fd;

	fd = open("resources/maps/map00_1", O_RDONLY);
	m = t_map_read(fd, "Plateau", 0);
	close(fd);
	while (1)
	{
		t_map_print(&m);
		if (!t_map_expand(&m, CELL_O))
			break;
		if (!t_map_expand(&m, CELL_X))
			break;
	}
	t_map_print(&m);
}

int main()
{
	test_piece_trim();
	test_expand();
}
