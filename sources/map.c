/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 12:18:35 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 01:03:38 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

inline static int	elems_action(char **elems, char *line, int mode)
{
	int		it;

	if (!elems)
		return (0);
	if (mode == 0 && !(it = 0))
		while (elems[it])
			it++;
	else if (mode == 1 && (it = -1))
	{
		while (elems[++it])
			free(elems[it]);
		free(elems);
		free(line);
	}
	return (mode ? 0 : it);
}

inline static int	add_player_data(t_game *game, int fd)
{
	char	**elems;
	char	*line;

	ft_get_next_line(fd, &line);
	if (elems_action((elems = ft_strsplit(line, ' ')), 0, 0) != 2)
		return (0);
	game->p_pos.x = ft_atoi(elems[1]) - 0.5;
	game->p_pos.y = ft_atoi(elems[0]) - 0.5;
	elems_action(elems, line, 1);
	if (game->p_pos.x <= 1 || game->p_pos.x > game->map.w - 1
		|| game->p_pos.y <= 1 || game->p_pos.y > game->map.h - 1)
		return (0);
	return (1);
}

inline static int	run_data(long **data, t_game *gd)
{
	int		i;
	int		j;

	if (data[(int)gd->p_pos.x][(int)gd->p_pos.y] & 0xFFFF)
		return (0);
	i = -1;
	while (++i < gd->map.w && (j = -1))
		while (++j < gd->map.h)
			if (IS_WALL(data[i][j]) || i == 0 || j == 0
				|| i == gd->map.w - 1 || j == gd->map.h - 1)
			{
				!(data[i][j] & 0xFL) ? data[i][j] |= 0x1L : 0;
				!(data[i][j] & 0xF0L) ? data[i][j] |= 0x10L : 0;
				!(data[i][j] & 0xF00L) ? data[i][j] |= 0x100L : 0;
				!(data[i][j] & 0xF000L) ? data[i][j] |= 0x1000L : 0;
			}
			else
			{
				!(data[i][j] & 0xF0000L) ? data[i][j] |= 0x10000L : 0;
				!(data[i][j] & 0xF00000L) ? data[i][j] |= 0x100000L : 0;
			}
	return (1);
}

inline static int	read_map(int fd, t_game *game, int rows, int cols)
{
	char	**elems;
	char	*line;
	int		it;
	int		w;

	if (rows <= 2 || rows > MAX_MAP_SIZE || cols <= 2 || cols > MAX_MAP_SIZE)
		return (0);
	game->map.w = rows;
	game->map.h = cols;
	game->map.data = ft_memalloc(sizeof(long *) * rows);
	it = -1;
	while (++it < rows)
		game->map.data[it] = ft_memalloc(sizeof(long) * cols);
	if ((it = -1) && !add_player_data(game, fd))
		return (0);
	while (ft_get_next_line(fd, &line) == 1 && ++it < rows && (w = -1))
	{
		if (elems_action((elems = ft_strsplit(line, ' ')), 0, 0) != cols)
			return (0);
		while (++w < cols)
			game->map.data[it][w] = ft_atol_base(elems[w], 16);
		elems_action(elems, line, 1);
	}
	return (it == rows - 1 ? run_data(game->map.data, game) : 0);
}

void				load_map(t_game *game, int level)
{
	static char	map[] = MAPS_FOLDER"level1.map";
	char		**elems;
	char		*line;
	int			fd;

	map[ft_strlen(map) - 5] = level + '0';
	if ((fd = open(map, O_RDONLY)) == -1)
	{
		ft_err_handler(map, "Couldn't find map", 0, 0);
		if ((fd = open(MAPS_FOLDER"level1.map", O_RDONLY)) == -1)
			ft_err_handler(map, "Couldn't find map", 0, 1);
	}
	if (ft_get_next_line(fd, &line) != 1
		|| elems_action((elems = ft_strsplit(line, ' ')), 0, 0) != 2)
		return (ft_err_handler(map, "map invalid!", 0, 1));
	if (!read_map(fd, game, ft_atoi(elems[0]), ft_atoi(elems[1])))
		ft_err_handler(map, "map invalid!", 0, 1);
	elems_action(elems, line, 1);
	close(fd);
}
