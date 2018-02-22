/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:13:55 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 01:28:42 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		SDL_main(int argc, char *argv[])
{
	t_game			gd;
	t_sgl_window	*win;
	static void		(*draw_deps[])() = {
		ft_draw_menu, ft_draw_levels, ft_draw_game, death_cam};

	sgl_init();
	load_media(&gd);
	win = sgl_new_window(PROGRAM_NAME, 1280, 960, SDL_WINDOW_OPENGL);
	init_game(&gd);
	while (1)
	{
		gd.screen = win->surface;
		SDL_ShowCursor(SDL_DISABLE);
		draw_deps[gd.state](win->surface, &gd);
		expose_actions(gd);
		if (!poll_event(&gd))
			return (0);
		gd.state == 1 ? level_selector_mouse_hover(gd) : 0;
		gd.move && gd.state == 2 ? move(&gd, gd.move * gd.mov_speed) : 0;
		gd.rotate && gd.state == 2 ? rotate(&gd, gd.rotate * gd.rot_speed) : 0;
		SDL_UpdateWindowSurface(win->p);
		sgl_vsync();
	}
	return (sgl_quit());
}
