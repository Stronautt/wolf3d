/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_resize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:07:29 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/10 21:48:42 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_resize_window(t_uint wind_id, int new_width, int new_height)
{
	t_sgl_window	*win;

	if (!(win = sgl_get_window_by_id(wind_id)))
		return ;
	win->width = new_width;
	win->height = new_height;
	!(win->surface = SDL_GetWindowSurface(win->p))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
}
