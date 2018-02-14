/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_selector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:45:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/12 15:49:12 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	level_selector_mouse_hover(t_game gd)
{
	int						i;
	int						x;
	int						y;
	static const t_button	bt[] = {
		{3.5, 1.75, 17, 12.2, 1, ""}, {3.5, 1.53, 17, 12.2, 2, ""},
		{3.5, 1.36, 17, 12.2, 3, ""}, {2.5, 1.75, 17, 12.2, 4, ""},
		{2.5, 1.53, 17, 12.2, 5, ""}, {2.5, 1.36, 17, 12.2, 6, ""},
		{3.5, 1.23, 17, 12.2, 0, ""}, {.caption = NULL}};

	SDL_GetMouseState(&x, &y);
	i = -1;
	while (bt[++i].caption)
		if (x >= gd.screen->w / bt[i].x && y >= gd.screen->h / bt[i].y
			&& x <= gd.screen->w / bt[i].x + gd.screen->w / bt[i].w
			&& y <= gd.screen->h / bt[i].y + gd.screen->h / bt[i].h)
			sgl_draw_str("-", &(t_font){"wolfenstein", gd.screen->h / 20,
				0xFF0000, 0}, (t_point){gd.screen->w / bt[i].x - 30,
				gd.screen->h / bt[i].y, 0}, gd.screen);
}

void	level_selector_mouse(SDL_MouseButtonEvent e, t_game *gd)
{
	int						i;
	static const t_button	bt[] = {
		{3.5, 1.75, 17, 12.2, 1, ""}, {3.5, 1.53, 17, 12.2, 2, ""},
		{3.5, 1.36, 17, 12.2, 3, ""}, {2.5, 1.75, 17, 12.2, 4, ""},
		{2.5, 1.53, 17, 12.2, 5, ""}, {2.5, 1.36, 17, 12.2, 6, ""},
		{3.5, 1.23, 17, 12.2, 0, ""}, {.caption = NULL}};

	if (e.button == SDL_BUTTON_LEFT && (i = -1))
		while (bt[++i].caption)
			if (e.x >= gd->screen->w / bt[i].x && e.y >= gd->screen->h / bt[i].y
				&& e.x <= gd->screen->w / bt[i].x + gd->screen->w / bt[i].w
				&& e.y <= gd->screen->h / bt[i].y + gd->screen->h / bt[i].h)
			{
				if (bt[i].act == 0 && !(gd->state = 0))
					return ;
				gd->state = 2;
				load_map(gd, bt[i].act);
				Mix_HaltMusic();
			}
}

void	ft_draw_levels(SDL_Surface *screen, t_game *gd)
{
	int						i;
	static const t_button	bt[] = {
		{3.5, 1.75, 17, 12.2, 0, "Level 1"},
		{3.5, 1.53, 17, 12.2, 0, "Level 2"},
		{3.5, 1.36, 17, 12.2, 0, "Level 3"},
		{2.5, 1.75, 17, 12.2, 0, "Level 4"},
		{2.5, 1.53, 17, 12.2, 0, "Level 5"},
		{2.5, 1.36, 17, 12.2, 0, "Level 6"},
		{3.5, 1.23, 17, 12.2, 0, "Back"}, {.caption = NULL}};

	SDL_ShowCursor(SDL_ENABLE);
	Mix_PlayingMusic() == 0 ? Mix_PlayMusic(gd->menu_sound, -1) : 0;
	ft_bzero(screen->pixels, screen->w * screen->h * 4);
	SDL_BlitScaled(gd->menu_bg, NULL, screen, NULL);
	sgl_draw_str("Select level", &(t_font){"wolfenstein", screen->h / 5,
		0xFFFFFF, 0}, (t_point){screen->w / 5, screen->h / 5, 0}, screen);
	i = -1;
	while (bt[++i].caption)
		sgl_draw_str(bt[i].caption, &(t_font){"wolfenstein", screen->h / 20,
				0xFFFFFF, 0}, (t_point){screen->w / bt[i].x,
					screen->h / bt[i].y, 0}, screen);
}
