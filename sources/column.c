/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:04:35 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 19:04:35 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_uint		*texel(SDL_Surface *s, int x, int y)
{
	if (x >= 0 && x < s->w && y >= 0 && y < s->h)
		return ((t_uint *)s->pixels + y * (s->pitch / 4) + x);
	return (NULL);
}

static void	plot(t_uint *px, t_uint *t, t_uint mask, char sprite)
{
	t_uint	v;

	v = t ? (mask ? *t & mask : *t) : 0;
	v || !sprite ? *px = v : 0;
}

void		draw_column(SDL_Surface *dst, int x, t_col c)
{
	double	ratio;
	int		pitch;
	int		end;
	int		y;
	int		sy;

	if (!c.src && c.sprite)
		return ;
	pitch = dst->pitch / 4;
	ratio = (double)c.src_h / c.h;
	y = c.y < 0 ? -1 : c.y - 1;
	end = c.y + c.h < dst->h - HUD_H(dst) ? c.y + c.h : dst->h - HUD_H(dst);
	while (++y < end)
	{
		sy = (y - c.y) * ratio;
		plot((t_uint *)dst->pixels + y * pitch + x, c.src && sy >= 0
			&& sy < c.src_h ? c.src + sy * c.step : NULL, c.mask, c.sprite);
	}
}

static void	floor_pair(t_game *gd, t_draw *d, t_point p)
{
	long	n;
	int		pitch;
	t_uint	*px;

	n = gd->map.data[(int)p.x][(int)p.y];
	p.x -= (int)p.x;
	p.y -= (int)p.y;
	pitch = gd->screen->pitch / 4;
	px = (t_uint *)gd->screen->pixels + d->map[2];
	if (d->y - 1 < gd->screen->h - HUD_H(gd->screen))
		plot(px + (d->y - 1) * pitch, texel(gd->s_t[F_T(n)],
			p.y * gd->s_t[F_T(n)]->w, p.x * gd->s_t[F_T(n)]->h),
			gd->mlg_m[0], 0);
	plot(px + (d->h - d->y) * pitch, texel(gd->s_t[C_T(n)],
		p.y * gd->s_t[C_T(n)]->w, p.x * gd->s_t[C_T(n)]->h), gd->mlg_m[1], 0);
}

void		ft_draw_floor_ceil(t_game *gd, double wall_dist, t_point r_d,
								t_draw d)
{
	t_point	coords;
	double	wh;

	if (!r_d.z && r_d.x > 0 && (coords.x = d.map[0]))
		coords.y = d.map[1] + d.wall_x;
	else if (!r_d.z && r_d.x < 0 && (coords.x = d.map[0] + 1.0))
		coords.y = d.map[1] + d.wall_x;
	else if (r_d.z && r_d.y > 0 && (coords.y = d.map[1]))
		coords.x = d.map[0] + d.wall_x;
	else if ((coords.y = d.map[1] + 1.0))
		coords.x = d.map[0] + d.wall_x;
	while (++d.y <= d.h)
	{
		wh = d.h / (2.0 * d.y - d.h) / wall_dist;
		floor_pair(gd, &d, (t_point){wh * coords.x + (1.0 - wh) * gd->p_pos.x,
			wh * coords.y + (1.0 - wh) * gd->p_pos.y, 0});
	}
}
