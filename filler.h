#ifndef FILLER_H
# define FILLER_H

typedef struct s_filler_map
{
	int m;
	int n;
	char **data;
} t_map;

t_map read_map(char *name);

#endif
