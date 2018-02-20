/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_imgload.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:58:44 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

SDL_Surface	*sgl_imgload(char *path)
{
	SDL_Surface	*ret;
	SDL_Surface	*tmp;

	if (!(tmp = IMG_Load(path)))
		return (NULL);
	ret = SDL_ConvertSurface(tmp, SDL_ISPIXELFORMAT_ALPHA(tmp->format)
		|| SDL_ISPIXELFORMAT_INDEXED(tmp->format)
		|| SDL_SurfaceHasColorKey(tmp) ? SDL_PIXELFORMAT_ARGB8888 : SGL_FORMAT);
	SDL_DestroySurface(tmp);
	return (ret);
}
