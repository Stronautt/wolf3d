/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:37:28 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/10 13:47:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_draw_line(t_point a, t_point b, t_uint color, SDL_Surface *surface)
{
	t_uint	*pixels;
	double	t;
	double	k;
	int		dx;
	int		dy;

	pixels = (t_uint *)surface->pixels;
	k = 1.0 / sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
	t = -k;
	while ((t += k) <= 1.0)
	{
		dx = ROUND(a.x + (b.x - a.x) * t);
		dy = ROUND(a.y + (b.y - a.y) * t);
		if (dy >= 0 && dy < surface->h && dx >= 0 && dx < surface->w)
			pixels[dy * surface->w + dx] = color;
	}
}
