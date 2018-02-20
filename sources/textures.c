/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:20:51 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 19:20:51 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*load_wall(char *path)
{
	SDL_Surface	*s;
	SDL_Surface	*t;
	int			x;
	int			y;

	if (!(s = sgl_imgload(path)))
		return (NULL);
	if ((t = SDL_CreateSurface(s->h, s->w, s->format)) && (y = -1))
		while (++y < s->h && (x = -1))
			while (++x < s->w)
				*texel(t, y, x) = *texel(s, x, y);
	SDL_DestroySurface(s);
	return (t);
}
