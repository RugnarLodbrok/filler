#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static void t_map_flip_xo(t_map *m)
{
	int i;
	int j;

	i = 0;
	while (i < m->m)
	{
		j = 0;
		while (j < m->n)
		{
			if (m->data[i][j] == CELL_O)
				m->data[i][j] = CELL_X;
			else if (m->data[i][j] == CELL_X)
				m->data[i][j] = CELL_O;
			j++;
		}
		i++;
	}
}

static char read_turn(int fd)
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

static t_point read_filler_map_header(int fd, const char *name)
{
	char *s;
	char **words;
	char **ptr;
	t_point r;

	if (get_next_line(fd, &s) <= 0)
		ft_error_exit("error");
	words = ft_strsplit(s, ' ');
	if (ft_strcmp(words[0], name))
		ft_error_exit("error; got `%s` expected %s at the 1st place", s, name);
	if (!(r.x = ft_atoi(words[1])))
		ft_error_exit("error; got %s, expected number at the 2nd place", s);
	if (!(r.y = ft_atoi(words[2])))
		ft_error_exit("error; got %s, expected number at the 3rd place", s);
	free(s);
	ptr = words;
	while (*ptr)
		free(*ptr++);
	free(words);
	return (r);
}

t_map t_map_read(int fd, char *name, int skip_margin)
{
	t_map m;
	t_point size;
	int i;

	ft_bzero(&m, sizeof(m));
	size = read_filler_map_header(fd, name);
	m.m = size.x;
	m.n = size.y;
	i = 0;
	if (!(m.data = malloc(sizeof(char *) * (m.m + 1))))
		ft_error_exit("memory error");
	m.data[m.m] = 0;
	if (skip_margin)
	{
		m.offset.y = 4;
		get_next_line(fd, m.data);
	}
	while (i < m.m)
	{
		if (get_next_line(fd, m.data + i) <= 0)
			ft_error_exit("error during reading map data");
		m.data[i] += m.offset.y;
		ft_toupper_inplace(m.data[i]);
		i++;
	}
	return m;
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
