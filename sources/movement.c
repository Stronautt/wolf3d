/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 19:12:13 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 01:30:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	shoot_dda(int *map, t_game *gd)
{
	t_point	r_d;
	t_point	sd_dist;
	t_point	step;
	int		path;

	r_d.x = gd->dir.x + gd->plane.x * (2 * map[2] / (double)gd->screen->w - 1);
	r_d.y = gd->dir.y + gd->plane.y * (2 * map[2] / (double)gd->screen->w - 1);
	step.x = r_d.x < 0 ? -1 : 1;
	step.y = r_d.y < 0 ? -1 : 1;
	sd_dist.x = r_d.x < 0 ? (gd->p_pos.x - map[0]) * ABS(1 / r_d.x)
						: (map[0] + 1.0 - gd->p_pos.x) * ABS(1 / r_d.x);
	sd_dist.y = r_d.y < 0 ? (gd->p_pos.y - map[1]) * ABS(1 / r_d.y)
						: (map[1] + 1.0 - gd->p_pos.y) * ABS(1 / r_d.y);
	path = -1;
	while (++path < 10)
	{
		sd_dist.x < sd_dist.y ? map[0] += step.x : 0;
		sd_dist.x >= sd_dist.y ? map[1] += step.y : 0;
		sd_dist.x < sd_dist.y ? (sd_dist.x += ABS(1 / r_d.x))
								: (sd_dist.y += ABS(1 / r_d.y));
		if (SPRITE(gd->map.data[map[0]][map[1]]) == 5
			|| IS_WALL(gd->map.data[map[0]][map[1]]))
			break ;
	}
}

void	move(t_game *g, double d)
{
	double		w;
	long		**map;
	long		tmp;

	map = g->map.data;
	w = d > 0 ? 0.35 : -0.35;
	tmp = map[(int)(g->p_pos.x + g->dir.x * (w + d))]
			[(int)g->p_pos.y - (int)(g->dir.y * w)];
	!IS_WALL(tmp) && (!IS_SSPRITE(tmp) || SPRITE(tmp) == 7)
		? g->p_pos.x += g->dir.x * d : 0;
	tmp = map[(int)g->p_pos.x - (int)(g->dir.x * w)]
			[(int)(g->p_pos.y + g->dir.y * (w + d))];
	!IS_WALL(tmp) && (!IS_SSPRITE(tmp) || SPRITE(tmp) == 7)
		? g->p_pos.y += g->dir.y * d : 0;
	tmp = map[(int)g->p_pos.x][(int)g->p_pos.y];
	SPRITE(tmp) ? item_actions(g,
		&map[(int)g->p_pos.x][(int)g->p_pos.y], SPRITE(tmp)) : 0;
}

void	rotate(t_game *game, double delta)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir.x;
	game->dir.x = game->dir.x * cos(delta) - game->dir.y * sin(delta);
	game->dir.y = old_dir_x * sin(delta) + game->dir.y * cos(delta);
	old_plane_x = game->plane.x;
	game->plane.x = game->plane.x * cos(delta) - game->plane.y * sin(delta);
	game->plane.y = old_plane_x * sin(delta) + game->plane.y * cos(delta);
}
