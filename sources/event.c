/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phrytsenko <phrytsenko@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:28:09 by pgritsen          #+#    #+#             */
/*   Updated: 2018/08/09 11:41:21 by phrytsenko       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

inline static void	key_down(SDL_Scancode key, t_game *game)
{
	key == SDL_SCANCODE_W && game->state == 2 ? game->move = 1 : 0;
	key == SDL_SCANCODE_A && game->state == 2 ? game->rotate = 1 : 0;
	key == SDL_SCANCODE_S && game->state == 2 ? game->move = -1 : 0;
	key == SDL_SCANCODE_D && game->state == 2 ? game->rotate = -1 : 0;
	key == SDL_SCANCODE_LSHIFT && game->state == 2 ? (game->mov_speed = 0.13)
						&& (game->rot_speed = 0.07) : 0;
	key == SDL_SCANCODE_RETURN ? game->inputmode = 1 - game->inputmode : 0;
	if (key == SDL_SCANCODE_SPACE && game->state == 2
		&& SDL_GetTicks() - game->shoot > 400)
		shoot(game);
}

inline static void	key_up(SDL_Event e, SDL_Scancode key, t_game *game)
{
	SDL_Window		*win;
	static char		full_screen;

	if ((key == SDL_SCANCODE_W || key == SDL_SCANCODE_S) && game->state == 2)
		game->move = 0;
	if ((key == SDL_SCANCODE_A || key == SDL_SCANCODE_D) && game->state == 2)
		game->rotate = 0;
	key == SDL_SCANCODE_LSHIFT && game->state == 2 ? (game->mov_speed = 0.08)
						&& (game->rot_speed = 0.05) : 0;
	if (key == SDL_SCANCODE_TAB && e.window.windowID)
	{
		win = sgl_get_window_by_id(e.window.windowID)->p;
		full_screen && !(full_screen = 0) ? SDL_SetWindowFullscreen(win, 0)
			: (full_screen = 1) &&
				SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}

inline static void	trace_input(SDL_KeyboardEvent key, t_game *gd)
{
	static size_t	it;

	if (gd->state != 2 || !gd->inputmode)
		return (key_down(key.keysym.scancode, gd));
	if (key.keysym.scancode == SDL_SCANCODE_RETURN && !(it = 0))
	{
		if (!ft_strcmp(gd->command, "raisethesun"))
			(gd->health = 100) && (gd->score -= 10000);
		else if (!ft_strcmp(gd->command, "godmode"))
			gd->godmode = 1 - gd->godmode;
		else if (!ft_strncmp(gd->command, "goto ", 5))
			reload_map(gd, ft_atoi(gd->command + 5), 1);
		else if (!ft_strcmp(gd->command, "displaymap"))
			(gd->mapdisplay = 1 - gd->mapdisplay) && (gd->score -= 2000);
		else if (!ft_strcmp(gd->command, "exit"))
			exit(0);
		ft_bzero(gd->command, sizeof(gd->command));
		gd->inputmode = 0;
	}
	else if (it < sizeof(gd->command) - 1 && ft_isprint(key.keysym.sym))
		gd->command[it++] = key.keysym.sym;
	else if (key.keysym.sym == SDLK_BACKSPACE && it > 0)
		gd->command[--it] = 0;
}

int					poll_event(t_game *game)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE
			|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == EXIT_KEY))
			return (sgl_quit());
		else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			sgl_resize_window(e.window.windowID, e.window.data1,
										e.window.data2);
		else if (e.type == SDL_KEYDOWN)
			trace_input(e.key, game);
		else if (e.type == SDL_KEYUP)
			key_up(e, e.key.keysym.scancode, game);
		else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 0)
			menu_mouse(e.button, game);
		else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 1)
			level_selector_mouse(e.button, game);
		else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 3)
			death_cam_mouse(e.button, game);
	return (1);
}
