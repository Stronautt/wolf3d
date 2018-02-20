/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:49:37 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	ft_dda(t_game *gd, t_point *r_dir, int *map, t_spr *s)
{
	t_dda	d;

	dda_init(gd, r_dir, map, &d);
	while (1)
	{
		d.sd_dist.x < d.sd_dist.y ? map[0] += d.step.x : 0;
		d.sd_dist.x >= d.sd_dist.y ? map[1] += d.step.y : 0;
		if (d.sd_dist.x < d.sd_dist.y && !(r_dir->z = 0))
			d.sd_dist.x += d.delta.x;
		else if ((r_dir->z = 1))
			d.sd_dist.y += d.delta.y;
		if (IS_WALL(gd->map.data[map[0]][map[1]]))
			break ;
		if (SPRITE(gd->map.data[map[0]][map[1]]) && s->n < SPRITES_PER_RAY)
			ft_memcpy(s->cell[s->n++], map, sizeof(s->cell[0]));
	}
	return (!r_dir->z
			? (map[0] - gd->p_pos.x + (1.0 - d.step.x) / 2.0) / r_dir->x
			: (map[1] - gd->p_pos.y + (1.0 - d.step.y) / 2.0) / r_dir->y);
}

void	ft_draw_wall(t_game *gd, double wall_dist, t_point r_d, int map[3])
{
	int		l_height;
	int		y_start;
	long	tex_n;
	double	wall_x;
	double	tex_x;

	l_height = (double)gd->screen->h / wall_dist;
	y_start = (gd->screen->h - l_height) / 2;
	l_height = gd->screen->h - 2 * y_start;
	if (r_d.z)
		tex_n = r_d.y > 0 ? TOP_WALL(gd->map.data[map[0]][map[1]])
							: BOT_WALL(gd->map.data[map[0]][map[1]]);
	else
		tex_n = r_d.x > 0 ? LEFT_WALL(gd->map.data[map[0]][map[1]])
							: RIGHT_WALL(gd->map.data[map[0]][map[1]]);
	wall_x = !r_d.z ? ft_get_fractional(gd->p_pos.y + wall_dist * r_d.y)
						: ft_get_fractional(gd->p_pos.x + wall_dist * r_d.x);
	tex_x = (!r_d.z && r_d.x > 0) || (r_d.z && r_d.y < 0)
		? gd->w_t[tex_n]->h - wall_x * ((double)gd->w_t[tex_n]->h - 1)
		: wall_x * (double)gd->w_t[tex_n]->h;
	tex_x >= gd->w_t[tex_n]->h ? tex_x = gd->w_t[tex_n]->h - 1 : 0;
	draw_column(gd->screen, map[2], (t_col){texel(gd->w_t[tex_n], 0, tex_x),
		1, gd->w_t[tex_n]->w, y_start, l_height, gd->mlg_m[(int)r_d.z], 0});
	ft_draw_floor_ceil(gd, wall_dist, r_d,
		(t_draw){map, wall_x, l_height + y_start, gd->screen->h});
}

void	ft_draw_column(t_game *gd, int x)
{
	int		map_xy[3];
	double	wall_dist;
	double	camera_x;
	t_point	ray_dir;
	t_spr	s;

	camera_x = 2.0 * x / (double)gd->screen->w - 1.0;
	ray_dir.x = gd->dir.x + gd->plane.x * camera_x;
	ray_dir.y = gd->dir.y + gd->plane.y * camera_x;
	map_xy[0] = (int)gd->p_pos.x;
	map_xy[1] = (int)gd->p_pos.y;
	map_xy[2] = x;
	s.n = 0;
	wall_dist = ft_dda(gd, &ray_dir, map_xy, &s);
	wall_dist < MIN_WALL_DIST ? wall_dist = MIN_WALL_DIST : 0;
	ft_draw_wall(gd, wall_dist, ray_dir, map_xy);
	while (s.n-- > 0)
		draw_sprite(gd, s.cell[s.n]);
}

void	ft_draw_heart(t_game *gd, SDL_AtomicInt *next)
{
	int		x;
	int		end;

	while ((x = SDL_AddAtomicInt(next, 1) * RENDER_CHUNK) < gd->screen->w)
	{
		end = x + RENDER_CHUNK;
		while (x < end && x < gd->screen->w)
			ft_draw_column(gd, x++);
	}
}

void	ft_draw_game(SDL_Surface *screen, t_game *gd)
{
	!sgl_playing(MUSIC_CHANNEL) && !sgl_playing(MLG_CHANNEL)
		? sgl_play(MUSIC_CHANNEL, gd->game_sound, -1) : 0;
	render_frame(gd);
	enemy_actions(gd);
	ft_draw_hud(gd);
	draw_effects(gd);
	display_fps(screen, gd->fpsdisplay);
}
