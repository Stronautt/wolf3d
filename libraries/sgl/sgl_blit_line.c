/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_blit_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:48:14 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/04 20:25:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_blit_line(SDL_Surface *src, SDL_Surface *dst,
						SDL_Rect src_r, SDL_Rect dst_r)
{
	int		y;
	int		limit;
	int		surface_y;
	long	pixel;

	y = dst_r.y - 1;
	limit = dst_r.y + dst_r.h;
	limit >= dst->h ? limit = dst->h : 0;
	y < 0 ? y = 0 : 0;
	while (++y < limit)
	{
		surface_y = (y - dst_r.y) * ((double)src->h / dst_r.h);
		pixel = sgl_get(src, src_r.x, surface_y);
		sgl_plot((t_point){dst_r.x, y, 0}, pixel, dst);
	}
}
