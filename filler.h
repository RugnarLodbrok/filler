/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:24:00 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/23 16:24:02 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define CELL_EMPTY '.'
# define CELL_FULL '*'
# define CELL_X 'X'
# define CELL_O 'O'

typedef struct	s_filler_map
{
	int		m;
	int		n;
	t_point	offset;
	char	**data;
}				t_map;

typedef struct	s_game_state
{
	char	turn;
	t_map	map;
	t_map	piece;
}				t_game_state;

int				read_game_state(int fd, t_game_state *s);
int				t_map_can_place(t_map *map, t_map *piece, t_point p);
void			t_map_place(t_map *map, t_map *piece, t_point p);
void			t_map_copy(t_map *dst, t_map *src);
void			t_map_del(t_map *m);
int				t_map_score(t_map *m);
void			t_map_trim(t_map *piece);

#endif
