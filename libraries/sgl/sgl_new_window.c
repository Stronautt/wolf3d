/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:57:02 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_sgl_window	*sgl_new_window(char *title, int width, int height, t_uint wm)
{
	SDL_Surface		*icon;
	t_sgl_window	*new;

	if ((new = sgl_get_window(title)))
		return (new);
	if (!(new = ft_memalloc(sizeof(t_sgl_window))))
		s_err_handler("SGL", "Couldn't create window.", 0, 1);
	new->title = ft_strdup(title);
	if (!(new->p = SDL_CreateWindow(title, width, height, wm))
		|| !SDL_GetWindowSizeInPixels(new->p, &new->width, &new->height))
		s_err_handler("SDL", SDL_GetError(), 0, 1);
	new->id = SDL_GetWindowID(new->p);
	if (!(icon = sgl_imgload(ICON_PATH)))
		s_err_handler(ICON_PATH, "File doesn't exist", 0, 0);
	SDL_SetWindowIcon(new->p, icon);
	SDL_DestroySurface(icon);
	!(new->surface = SDL_CreateSurface(new->width, new->height, SGL_FORMAT))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
	ft_dlstpush(&g_win_list, ft_dlstnew(new, sizeof(new)));
	return (new);
}
