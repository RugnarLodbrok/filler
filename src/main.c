/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:26:31 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/23 16:26:34 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include "libft_compat.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static int	get_move_score(t_game_state *s, t_point p)
{
	int		score;
	t_map	map2;

	if (!t_map_can_place(&s->map, &s->piece, p))
		return (INT_MIN);
	t_map_copy(&map2, &s->map);
	t_map_place(&map2, &s->piece, p);
	score = t_map_score(&map2);
	t_map_del(&map2);
	return (score);
}

static char	read_turn(int fd)
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

static void	make_move(t_game_state *s)
{
	int		max_score;
	int		score;
	t_point	p;
	t_point	best_p;

	ft_bzero(&best_p, sizeof(t_point));
	max_score = INT_MIN;
	ft_bzero(&p, sizeof(p));
	p.x = -1;
	while (++p.x < s->map.m - s->piece.m + 1)
	{
		p.y = -1;
		while (++p.y < s->map.n - s->piece.n + 1)
		{
			score = get_move_score(s, p);
			if (score > max_score)
			{
				max_score = score;
				best_p = p;
			}
		}
	}
	ft_printf("%d %d\n",
			best_p.x - s->piece.offset.x,
			best_p.y - s->piece.offset.y);
}

int			main(int ac, char **av)
{
	int				fd;
	t_game_state	s;

	if (ac == 1)
	{
		s.turn = read_turn(0);
		while (read_game_state(0, &s))
			make_move(&s);
	}
	else
	{
		fd = open(av[1], O_RDONLY);
		s.turn = read_turn(fd);
		while (read_game_state(fd, &s))
			make_move(&s);
		close(fd);
	}
	return (0);
}
