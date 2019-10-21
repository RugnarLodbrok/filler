#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static t_point read_filler_map_header(const char *name)
{
	char *s;
	char **words;
	char **ptr;
	t_point r;

	if (get_next_line(0, &s) <= 0)
		ft_error_exit("error");
	words = ft_strsplit(s, ' ');
	if (ft_strcmp(words[0], name))
		ft_error_exit("error; expected %s", name);
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

t_map read_map(char *name)
{
	t_map m;
	t_point size;
	int i;

	ft_bzero(&m, sizeof(m));
	size = read_filler_map_header(name);
	m.m = size.x;
	m.n = size.y;
	i = 0;
	if (!(m.data = malloc(sizeof(char *) * (m.m + 1))))
		ft_error_exit("memory error");
	m.data[m.m] = 0;
	while (i < m.m)
	{
		if (get_next_line(0, m.data + i) <= 0)
			ft_error_exit("error during reading map data");
		i++;
	}
	return m;
}
