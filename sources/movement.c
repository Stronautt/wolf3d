/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 19:12:13 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	dda_init(t_game *gd, t_point *r_dir, int *map, t_dda *d)
{
	d->step = (t_point){r_dir->x < 0 ? -1 : 1, r_dir->y < 0 ? -1 : 1, 0};
	d->delta = (t_point){ABS(1 / r_dir->x), ABS(1 / r_dir->y), 0};
	d->sd_dist.x = r_dir->x < 0 ? (gd->p_pos.x - map[0]) * d->delta.x
						: (map[0] + 1.0 - gd->p_pos.x) * d->delta.x;
	d->sd_dist.y = r_dir->y < 0 ? (gd->p_pos.y - map[1]) * d->delta.y
						: (map[1] + 1.0 - gd->p_pos.y) * d->delta.y;
}

void	shoot_dda(int *map, t_game *gd)
{
	t_point	r_d;
	t_dda	d;
	int		path;

	r_d.x = gd->dir.x + gd->plane.x * (2 * map[2] / (double)gd->screen->w - 1);
	r_d.y = gd->dir.y + gd->plane.y * (2 * map[2] / (double)gd->screen->w - 1);
	dda_init(gd, &r_d, map, &d);
	path = -1;
	while (++path < 10)
	{
		d.sd_dist.x < d.sd_dist.y ? map[0] += d.step.x : 0;
		d.sd_dist.x >= d.sd_dist.y ? map[1] += d.step.y : 0;
		d.sd_dist.x < d.sd_dist.y ? (d.sd_dist.x += d.delta.x)
								: (d.sd_dist.y += d.delta.y);
		if (IS_SSPRITE(gd->map.data[map[0]][map[1]])
			|| SPRITE(gd->map.data[map[0]][map[1]]) == 5
			|| IS_WALL(gd->map.data[map[0]][map[1]]))
			break ;
	}
}

void	move(t_game *g, double d)
{
	double		w;
	long		**map;
	long		tmp;

	d *= g->dt;
	map = g->map.data;
	w = d > 0 ? 0.35 : -0.35;
	tmp = map[(int)(g->p_pos.x + g->dir.x * (w + d))]
			[(int)g->p_pos.y];
	!IS_WALL(tmp) && (!IS_SSPRITE(tmp) || SPRITE(tmp) == 7)
		? g->p_pos.x += g->dir.x * d : 0;
	tmp = map[(int)g->p_pos.x]
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

	delta *= game->dt;
	old_dir_x = game->dir.x;
	game->dir.x = game->dir.x * cos(delta) - game->dir.y * sin(delta);
	game->dir.y = old_dir_x * sin(delta) + game->dir.y * cos(delta);
	old_plane_x = game->plane.x;
	game->plane.x = game->plane.x * cos(delta) - game->plane.y * sin(delta);
	game->plane.y = old_plane_x * sin(delta) + game->plane.y * cos(delta);
}
