/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_resize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:07:29 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

SDL_Surface	*sgl_resize_window(t_uint wind_id, int new_width, int new_height)
{
	t_sgl_window	*win;

	if (!(win = sgl_get_window_by_id(wind_id)))
		return (NULL);
	win->width = new_width;
	win->height = new_height;
	sgl_text_flush();
	destroy_fonts();
	SDL_DestroySurface(win->surface);
	!(win->surface = SDL_CreateSurface(new_width, new_height, SGL_FORMAT))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
	return (win->surface);
}
