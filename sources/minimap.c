/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:59:44 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 20:59:44 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_uint		cell_color(long n)
{
	if (IS_WALL(n))
		return (0xEFEFEF);
	if (IS_SSPRITE(n))
		return (0x8C);
	return (SPRITE(n) ? 0x8C8C00 : 0);
}

static SDL_Surface	*map_surface(t_game *gd)
{
	static SDL_Surface	*s;
	t_uint				*row;
	int					x;
	int					y;

	if (!s || s->w != gd->map.h || s->h != gd->map.w)
	{
		SDL_DestroySurface(s);
		if (!(s = SDL_CreateSurface(gd->map.h, gd->map.w, gd->screen->format)))
			ft_err_handler(SDL_GetError(), NULL, 0, 1);
	}
	y = -1;
	while (++y < gd->map.w && (x = -1))
	{
		row = (t_uint *)((char *)s->pixels + y * s->pitch);
		while (++x < gd->map.h)
			row[x] = cell_color(gd->map.data[y][x]);
	}
	return (s);
}

void				draw_map(t_game *gd)
{
	SDL_Rect	r;
	double		c;
	int			m;

	r = (SDL_Rect){gd->screen->w - gd->screen->w / 4, 10,
		gd->screen->w / (4 * gd->map.h) * gd->map.h, 0};
	!r.w ? r.w = gd->screen->w / 4 : 0;
	r.h = gd->map.w * r.w / gd->map.h;
	SDL_BlitSurfaceScaled(map_surface(gd), NULL, gd->screen, &r, r.w < gd->map.h
		? SDL_SCALEMODE_LINEAR : SDL_SCALEMODE_NEAREST);
	c = (double)r.w / gd->map.h;
	m = c / 1.5 < 3 ? 3 : c / 1.5;
	SDL_FillSurfaceRect(gd->screen, &(SDL_Rect){gd->p_pos.y * c + r.x - m / 2,
		gd->p_pos.x * c + r.y - m / 2, m, m}, 0x8C00);
}
