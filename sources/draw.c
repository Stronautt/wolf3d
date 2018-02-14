/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:49:37 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/14 00:25:30 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	ft_dda(t_game gd, t_point *r_dir, int *map)
{
	t_point	sd_dist;
	t_point	dlt_dist;
	t_point	step;

	dlt_dist.x = sqrt(1.0 + (r_dir->y * r_dir->y) / (r_dir->x * r_dir->x));
	dlt_dist.y = sqrt(1.0 + (r_dir->x * r_dir->x) / (r_dir->y * r_dir->y));
	step.x = r_dir->x < 0 ? -1 : 1;
	step.y = r_dir->y < 0 ? -1 : 1;
	sd_dist.x = r_dir->x < 0 ? (gd.p_pos.x - map[0]) * dlt_dist.x
						: (map[0] + 1.0 - gd.p_pos.x) * dlt_dist.x;
	sd_dist.y = r_dir->y < 0 ? (gd.p_pos.y - map[1]) * dlt_dist.y
						: (map[1] + 1.0 - gd.p_pos.y) * dlt_dist.y;
	while (1)
	{
		sd_dist.x < sd_dist.y ? map[0] += step.x : 0;
		sd_dist.x >= sd_dist.y ? map[1] += step.y : 0;
		if (sd_dist.x < sd_dist.y && !(r_dir->z = 0))
			sd_dist.x += dlt_dist.x;
		else if ((r_dir->z = 1))
			sd_dist.y += dlt_dist.y;
		if (IS_WALL(gd.map.data[map[0]][map[1]]))
			break ;
	}
	return (!r_dir->z ? (map[0] - gd.p_pos.x + (1.0 - step.x) / 2.0) / r_dir->x
			: (map[1] - gd.p_pos.y + (1.0 - step.y) / 2.0) / r_dir->y);
}

void	ft_draw_floor_ceil(t_game gd, double wall_dist, t_point r_d, t_draw d)
{
	t_point	coords;
	t_point	t;
	double	wh;
	long	n;

	if (!r_d.z && r_d.x > 0 && (coords.x = d.map[0]))
		coords.y = d.map[1] + d.wall_x;
	else if (!r_d.z && r_d.x < 0 && (coords.x = d.map[0] + 1.0))
		coords.y = d.map[1] + d.wall_x;
	else if (r_d.z && r_d.y > 0 && (coords.y = d.map[1]))
		coords.x = d.map[0] + d.wall_x;
	else if ((coords.y = d.map[1] + 1.0))
		coords.x = d.map[0] + d.wall_x;
	while (++d.y < d.h)
	{
		wh = d.h / (2.0 * d.y - d.h) / wall_dist;
		n = gd.map.data[(int)(wh * coords.x + (1.0 - wh) * gd.p_pos.x)]
					[(int)(wh * coords.y + (1.0 - wh) * gd.p_pos.y)];
		t.x = ft_get_fractional(wh * coords.x + (1.0 - wh) * gd.p_pos.x);
		t.y = ft_get_fractional(wh * coords.y + (1.0 - wh) * gd.p_pos.y);
		sgl_plot((t_point){d.map[2], d.y, 0}, sgl_get(gd.s_t[F_T(n)],
			t.y * gd.w_t[F_T(n)]->w, t.x * gd.w_t[F_T(n)]->h), gd.screen);
		sgl_plot((t_point){d.map[2], (d.h - d.y), 0}, sgl_get(gd.s_t[C_T(n)],
			t.y * gd.w_t[C_T(n)]->w, t.x * gd.w_t[C_T(n)]->h), gd.screen);
	}
}

void	ft_draw_wall(t_game gd, double wall_dist, t_point r_d, int map[3])
{
	int		l_height;
	int		y_start;
	long	tex_n;
	double	wall_x;
	double	tex_x;

	l_height = (double)gd.screen->h / wall_dist;
	y_start = -l_height / 2 + gd.screen->h / 2;
	if (r_d.z)
		tex_n = r_d.y > 0 ? TOP_WALL(gd.map.data[map[0]][map[1]])
							: BOT_WALL(gd.map.data[map[0]][map[1]]);
	else
		tex_n = r_d.x > 0 ? LEFT_WALL(gd.map.data[map[0]][map[1]])
							: RIGHT_WALL(gd.map.data[map[0]][map[1]]);
	wall_x = !r_d.z ? ft_get_fractional(gd.p_pos.y + wall_dist * r_d.y)
						: ft_get_fractional(gd.p_pos.x + wall_dist * r_d.x);
	tex_x = (!r_d.z && r_d.x > 0) || (r_d.z && r_d.y < 0)
		? gd.w_t[tex_n]->w - wall_x * ((double)gd.w_t[tex_n]->w - 1)
		: wall_x * (double)gd.w_t[tex_n]->w;
	sgl_blit_line(gd.w_t[tex_n], gd.screen,
					(SDL_Rect){tex_x, 0, 0, 0},
					(SDL_Rect){map[2], y_start, 0, l_height});
	ft_draw_floor_ceil(gd, wall_dist, r_d,
		(t_draw){map, wall_x, l_height + y_start, gd.screen->h, gd.screen->w});
}

void	ft_draw_heart(t_thread *t)
{
	int		x;
	int		map_xy[2];
	double	wall_dist;
	double	camera_x;
	t_point	ray_dir;

	x = t->start - 1;
	t->gd.screen = t->screen;
	while (++x < t->end)
	{
		camera_x = 2.0 * x / (double)t->screen->w - 1.0;
		ray_dir.x = t->gd.dir.x + t->gd.plane.x * camera_x;
		ray_dir.y = t->gd.dir.y + t->gd.plane.y * camera_x;
		map_xy[0] = (int)t->gd.p_pos.x;
		map_xy[1] = (int)t->gd.p_pos.y;
		wall_dist = ft_dda(t->gd, &ray_dir, map_xy);
		ft_draw_wall(t->gd, wall_dist, ray_dir,
					(int[3]){map_xy[0], map_xy[1], x});
	}
}

void	ft_draw_game(SDL_Surface *screen, t_game *gd)
{
	pthread_t	threads[THREADS];
	t_thread	d[THREADS];
	int			th;
	double		coef;

	Mix_PlayingMusic() == 0 ? Mix_PlayMusic(gd->game_sound, -1) : 0;
	ft_bzero(screen->pixels, screen->w * screen->h * 4);
	coef = screen->w / THREADS;
	th = -1;
	while (++th < THREADS)
	{
		d[th] = (t_thread){screen, *gd, ROUND((double)th * coef),
									ROUND((double)(th + 1) * coef)};
		pthread_create(&threads[th], NULL, (void *(*)())ft_draw_heart, &d[th]);
	}
	th = -1;
	while (++th < THREADS)
		pthread_join(threads[th], NULL);
	display_fps(screen);
	ft_draw_hud(gd);
}
