/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:28:09 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

inline static void	run_command(t_game *gd)
{
	if (!ft_strcmp(gd->command, "praisethesun"))
		(gd->health = 100) && (gd->score -= 10000);
	else if (!ft_strcmp(gd->command, "godmode"))
		gd->godmode = 1 - gd->godmode;
	else if (!ft_strncmp(gd->command, "goto ", 5))
		reload_map(gd, gd->command + 5, 1);
	else if (!ft_strcmp(gd->command, "displaymap"))
		(gd->mapdisplay = 1 - gd->mapdisplay) && (gd->score -= 2000);
	else if (!ft_strcmp(gd->command, "exit"))
		SDL_PushEvent(&(SDL_Event){SDL_EVENT_QUIT});
	else if (!ft_strcmp(gd->command, "fps"))
		gd->fpsdisplay = !gd->fpsdisplay;
	ft_bzero(gd->command, sizeof(gd->command));
}

inline static void	console_key(SDL_KeyboardEvent key, t_game *gd)
{
	size_t	len;

	len = ft_strlen(gd->command);
	if (key.scancode == SDL_SCANCODE_RETURN && !(gd->inputmode = 0))
		run_command(gd);
	else if (len < sizeof(gd->command) - 1 && ft_isprint(key.key))
		gd->command[len] = key.key;
	else if (key.key == SDLK_BACKSPACE && len)
		gd->command[len - 1] = 0;
}

inline static void	steer(t_game *gd)
{
	const bool	*kb;

	kb = SDL_GetKeyboardState(NULL);
	gd->move = !gd->inputmode * (kb[SDL_SCANCODE_W] - kb[SDL_SCANCODE_S]);
	gd->rotate = !gd->inputmode * (kb[SDL_SCANCODE_A] - kb[SDL_SCANCODE_D]);
	gd->mov_speed = kb[SDL_SCANCODE_LSHIFT] ? RUN_SPEED : WALK_SPEED;
	gd->rot_speed = kb[SDL_SCANCODE_LSHIFT] ? RUN_ROT : WALK_ROT;
}

inline static void	key_event(SDL_KeyboardEvent key, t_game *gd)
{
	SDL_Window	*win;

	if (!key.down && key.scancode == SDL_SCANCODE_F11
		&& (win = SDL_GetWindowFromID(key.windowID))
		&& !SDL_SetWindowFullscreen(win,
			!(SDL_GetWindowFlags(win) & SDL_WINDOW_FULLSCREEN)))
		ft_err_handler(SDL_GetError(), NULL, 0, 0);
	if (gd->state != 2 || (key.repeat && key.scancode == SDL_SCANCODE_RETURN))
		return ;
	if (key.down && gd->inputmode)
		console_key(key, gd);
	else if (key.down && key.scancode == SDL_SCANCODE_RETURN)
		gd->inputmode = 1;
	else if (key.down && key.scancode == SDL_SCANCODE_SPACE
		&& SDL_GetTicks() - gd->shoot > 400)
		shoot(gd);
	steer(gd);
}

int					poll_event(t_game *game)
{
	SDL_Event	e;
	static void	(*mouse_deps[])(SDL_Event *, t_game *) = {
		menu_mouse, level_selector_mouse, NULL, death_cam_mouse};

	while (SDL_PollEvent(&e))
		if (e.type == SDL_EVENT_QUIT
			|| (e.type == SDL_EVENT_KEY_DOWN && e.key.key == EXIT_KEY
				&& (game->state != 2 || !game->inputmode)))
		{
			render_quit();
			return (sgl_quit());
		}
		else if (e.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
			game->screen = sgl_resize_window(e.window.windowID, e.window.data1,
										e.window.data2);
		else if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP)
			key_event(e.key, game);
		else if (game->state != 2)
			mouse_deps[game->state](&e, game);
	return (1);
}
