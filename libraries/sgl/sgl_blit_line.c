/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_blit_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:48:14 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/15 21:37:34 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_blit_line(SDL_Surface *sur[2], SDL_Rect src_r,
						SDL_Rect dst_r, t_uint mask)
{
	int		y;
	int		limit;
	int		surface_y;
	long	pixel;

	y = dst_r.y - 1;
	limit = dst_r.y + dst_r.h;
	limit >= sur[1]->h ? limit = sur[1]->h : 0;
	y < 0 ? y = 0 : 0;
	while (++y < limit)
	{
		surface_y = (y - dst_r.y) * ((double)sur[0]->h / dst_r.h);
		pixel = sgl_get(sur[0], src_r.x, surface_y);
		mask ? pixel &= mask : 0;
		sgl_plot((t_point){dst_r.x, y, 0}, pixel, sur[1]);
	}
}
