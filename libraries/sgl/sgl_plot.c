/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_plot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:37:34 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/09 14:01:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_plot(t_point p, t_uint color, SDL_Surface *surface)
{
	int		dx;
	int		dy;
	t_uint	*pixels;

	pixels = (t_uint *)surface->pixels;
	dx = ROUND(p.x);
	dy = ROUND(p.y);
	if (dx >= 0 && dx < surface->w && dy >= 0 && dy < surface->h)
		pixels[dy * surface->w + dx] = color;
}
