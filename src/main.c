#include <fcntl.h>
#include "libft_compat.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

int get_move_score(t_game_state *s, t_point p)
{
	t_map map2;
	int score;

	if (!t_map_can_place(&s->map, &s->piece, p))
		return (-1);
	t_map_copy(&map2, &s->map);
	t_map_place(&map2, &s->piece, p);
	score = t_map_score(&map2);
	t_map_del(&map2);
	return (score);
}

char read_turn(int fd)
{
	char *s;
	char r;

	r = 0;
	if (get_next_line(fd, &s) <= 0)
		ft_error_exit("read error");
	if (ft_startswith(s, "$$$ exec p1"))
		r = CELL_O;
	else if (ft_startswith(s, "$$$ exec p2"))
		r = CELL_X;
	else
		ft_error_exit("bad first line: `%s`", s);
	free(s);
	return (r);
}

t_game_state read_game_state(int fd)
{
	t_game_state s;

	s.turn = read_turn(fd);
	s.map = t_map_read(fd, "Plateau", 1);
	s.piece = t_map_read(fd, "Piece", 0);
	t_map_trim(&s.piece);
	if (s.turn == CELL_O)
		t_map_flip_xo(&s.map);
	return s;
}

void make_move(int fd)
{
	t_game_state s;
	int max_score;
	int score;
	t_point p;
	t_point best_p;

	s = read_game_state(fd);
	max_score = -1;
	ft_bzero(&p, sizeof(p));
	for (p.x = 0; p.x < s.map.m - s.piece.m + 1; ++p.x)
	{
		for (p.y = 0; p.y < s.map.n - s.piece.n + 1; ++p.y)
		{
			score = get_move_score(&s, p);
			if (score > max_score)
			{
				max_score = score;
				best_p = p;
			}
		}

	}
	ft_printf("%d %d\n", best_p.x, best_p.y);
}

int main(int ac, char **av)
{
	int fd;

	if (ac == 1)
	{
		make_move(0);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	make_move(fd);
	close(fd);
	return (0);
}