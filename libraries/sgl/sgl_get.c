/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:32:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/02 13:39:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

inline t_uint	sgl_get(SDL_Surface *surface, int x, int y)
{
	t_uint	pixel;
	int		width;
	int		height;

	width = surface->w;
	height = surface->h;
	if (y >= 0 && y < height && x >= 0 && x < width)
		pixel = *((t_uint *)surface->pixels + y * width + x);
	else
		pixel = 0x000000;
	return (pixel);
}
