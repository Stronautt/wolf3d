/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:28:18 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 21:28:18 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_map(t_map *map)
{
	int		i;

	i = -1;
	while (map->data && ++i < map->w)
		free(map->data[i]);
	ft_memdel((void **)&map->data);
}

int		alloc_map(t_map *map, int rows, int cols)
{
	int		i;

	map->w = rows;
	map->h = cols;
	if (!(map->data = ft_memalloc(sizeof(long *) * rows)))
		return (0);
	i = -1;
	while (++i < rows)
		if (!(map->data[i] = ft_memalloc(sizeof(long) * cols)))
			return (0);
	return (1);
}

int		rest_is_blank(int fd)
{
	char	*line;
	int		blank;
	int		i;

	blank = 1;
	while (ft_get_next_line(fd, &line) == 1)
	{
		i = -1;
		while (line[++i])
			!ft_strchr(" \t\v\f\r", line[i]) ? blank = 0 : 0;
		free(line);
	}
	free(line);
	return (blank);
}

int		reload_map(t_game *gd, char *name, int pure)
{
	t_game	tmp;

	tmp = *gd;
	ft_bzero(&tmp.map, sizeof(tmp.map));
	if (!load_map(&tmp, name))
		return (0);
	free_map(&gd->map);
	init_game(gd);
	gd->map = tmp.map;
	gd->p_pos = tmp.p_pos;
	gd->state = 2;
	!pure ? gd->score = tmp.score : 0;
	!pure ? gd->health = tmp.health : 0;
	return (1);
}
