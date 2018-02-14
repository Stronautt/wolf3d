/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:28:09 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/12 18:22:56 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

inline static void	key_down(SDL_Keycode key, t_game *game)
{
	key == SDLK_w && game->state == 2 ? game->move = 1 : 0;
	key == SDLK_a && game->state == 2 ? game->rotate = 1 : 0;
	key == SDLK_s && game->state == 2 ? game->move = -1 : 0;
	key == SDLK_d && game->state == 2 ? game->rotate = -1 : 0;
	if (key == SDLK_SPACE && game->state == 2)
	{
		game->shoot = SDL_GetTicks() / 1000;
		Mix_PlayChannel(-1, game->shoot_sound, 0);
	}
	key == SDLK_LSHIFT && game->state == 2 ? (game->mov_speed = 0.13)
						&& (game->rot_speed = 0.07) : 0;
}

inline static void	key_up(SDL_Event e, SDL_Keycode key, t_game *game)
{
	SDL_Window		*win;
	static char		full_screen;

	(key == SDLK_w || key == SDLK_s) && game->state == 2 ? game->move = 0 : 0;
	(key == SDLK_a || key == SDLK_d) && game->state == 2 ? game->rotate = 0 : 0;
	key == SDLK_LSHIFT && game->state == 2 ? (game->mov_speed = 0.08)
						&& (game->rot_speed = 0.05) : 0;
	if (key == SDLK_TAB)
	{
		win = sgl_get_window_by_id(e.window.windowID)->p;
		full_screen && !(full_screen = 0)
			? SDL_SetWindowFullscreen(win, 0)
			: (full_screen = 1) &&
				SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}

int					poll_event(t_game *game)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
		if (e.window.event == SDL_WINDOWEVENT_CLOSE
			|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == EXIT_KEY))
			return (sgl_quit());
		else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			sgl_resize_window(e.window.windowID, e.window.data1,
										e.window.data2);
		else if (e.type == SDL_KEYDOWN)
			key_down(e.key.keysym.sym, game);
		else if (e.type == SDL_KEYUP)
			key_up(e, e.key.keysym.sym, game);
		else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 0)
			menu_mouse(e.button, game);
		else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 1)
			level_selector_mouse(e.button, game);
	return (1);
}
