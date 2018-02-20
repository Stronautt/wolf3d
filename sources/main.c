/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:13:55 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(void)
{
	static t_game	gd;
	t_sgl_window	*win;
	static void		(*draw_deps[])(SDL_Surface *, t_game *) = {
		ft_draw_menu, ft_draw_levels, ft_draw_game, death_cam};

	sgl_init();
	if (!SDL_GetBasePath() || chdir(SDL_GetBasePath()))
		ft_err_handler("Base path", SDL_GetBasePath(), errno, 1);
	load_media(&gd);
	win = sgl_new_window(PROGRAM_NAME, 1680, 1050, 0);
	init_game(&gd);
	while (1)
	{
		gd.screen = win->surface;
		gd.state != 2 ? SDL_ShowCursor() : SDL_HideCursor();
		draw_deps[gd.state](win->surface, &gd);
		expose_actions(&gd);
		if (!poll_event(&gd))
			return (0);
		gd.move && gd.state == 2 ? move(&gd, gd.move * gd.mov_speed) : 0;
		gd.rotate && gd.state == 2 ? rotate(&gd, gd.rotate * gd.rot_speed) : 0;
		sgl_update_window(win);
		gd.dt = sgl_vsync(win);
	}
}
