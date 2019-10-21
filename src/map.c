#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

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
		get_next_line(fd, m.data);
	while (i < m.m)
	{
		if (get_next_line(fd, m.data + i) <= 0)
			ft_error_exit("error during reading map data");
		m.data[i] += 4; //todo: after this we can't free this ptr anymore
		i++;
	}
	return m;
}

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

int t_map_score(t_map *m)
{
	(void)m;
	return (0);
}

void t_map_del(t_map *m)
{
	int i;

	i = 0;
	while (i < m->n)
	{
		free(m->data[i]);
		i++;
	}
}
