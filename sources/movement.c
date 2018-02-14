/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 19:12:13 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/12 15:57:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move(t_game *g, double d)
{
	double		w;
	long		**map;

	map = g->map.data;
	w = d > 0 ? 0.35 : -0.35;
	if (!IS_WALL(map[(int)(g->p_pos.x + g->dir.x * (w + d))]
					[(int)g->p_pos.y - (int)(g->dir.y * w)]))
		g->p_pos.x += g->dir.x * d;
	if (!IS_WALL(map[(int)g->p_pos.x - (int)(g->dir.x * w)]
					[(int)(g->p_pos.y + g->dir.y * (w + d))]))
		g->p_pos.y += g->dir.y * d;
	if (IS_PORTAL(map[(int)g->p_pos.x][(int)g->p_pos.y]))
		reload_map(g, IS_PORTAL(map[(int)g->p_pos.x][(int)g->p_pos.y]));
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
