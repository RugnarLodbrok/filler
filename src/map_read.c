/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:32:58 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/23 16:33:00 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static void		t_map_flip_xo(t_map *m)
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

static t_point	read_filler_map_header(int fd, const char *name)
{
	char	*s;
	char	**words;
	char	**ptr;
	t_point	r;
	int		status;

	if ((status = get_next_line(fd, &s)) < 0)
		ft_error_exit("error");
	if (!status || !ft_strlen(s))
		return (t_point){-1, -1};
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

static t_map	t_map_read(int fd, t_point size, int skip_margin)
{
	int		i;
	t_map	m;

	ft_bzero(&m, sizeof(m));
	m.m = size.x;
	m.n = size.y;
	if (m.m < 0)
		return (m);
	if (!(m.data = malloc(sizeof(char *) * (m.m + 1))))
		ft_error_exit("memory error");
	m.data[m.m] = 0;
	if (skip_margin)
		m.offset.y = 4;
	if (skip_margin)
		if (get_next_line(fd, m.data) > 0)
			free(m.data[0]);
	i = -1;
	while (++i < m.m)
	{
		if (get_next_line(fd, m.data + i) <= 0)
			ft_error_exit("error during reading map data");
		m.data[i] += m.offset.y;
		ft_toupper_inplace(m.data[i]);
	}
	return (m);
}

int				read_game_state(int fd, t_game_state *s)
{
	s->map = t_map_read(fd, read_filler_map_header(fd, "Plateau"), 1);
	if (s->map.m < 0)
		return (0);
	s->piece = t_map_read(fd, read_filler_map_header(fd, "Piece"), 0);
	t_map_trim(&s->piece);
	if (s->turn == CELL_O)
		t_map_flip_xo(&s->map);
	return (1);
}
