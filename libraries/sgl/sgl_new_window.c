/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:57:02 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/10 21:47:18 by pgritsen         ###   ########.fr       */
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
	new->width = width;
	new->height = height;
	new->title = ft_strdup(title);
	if (!(new->p = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, width, height, wm)))
		s_err_handler("SDL", SDL_GetError(), 0, 1);
	new->id = SDL_GetWindowID(new->p);
	if (!(icon = IMG_Load(ICON_PATH)))
		s_err_handler(ICON_PATH, "File doesn't exist", 0, 0);
	SDL_SetWindowIcon(new->p, icon);
	SDL_FreeSurface(icon);
	!(new->surface = SDL_GetWindowSurface(new->p))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
	ft_dlstpush(&g_win_list, ft_dlstnew(&new, sizeof(new)));
	return (new);
}
