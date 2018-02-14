/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:02:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/12 14:31:38 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	menu_mouse(SDL_MouseButtonEvent e, t_game *gd)
{
	int						i;
	static const t_button	bt[] = {
		{4.5, 1.75, 6.72, 12.2, 0, ""},
		{4.5, 1.53, 6.72, 12.2, 1, ""}, {.caption = NULL}};

	if (e.button == SDL_BUTTON_LEFT && (i = -1))
		while (bt[++i].caption)
			if (e.x >= gd->screen->w / bt[i].x && e.y >= gd->screen->h / bt[i].y
				&& e.x <= gd->screen->w / bt[i].x + gd->screen->w / bt[i].w
				&& e.y <= gd->screen->h / bt[i].y + gd->screen->h / bt[i].h)
			{
				bt[i].act == 1 ? exit(0) : 0;
				gd->state = bt[i].act + 1;
			}
}

void	ft_draw_menu(SDL_Surface *screen, t_game *gd)
{
	int						i;
	static SDL_Surface		*bt_tex;
	static const t_button	bt[] = {
		{4.5, 1.75, 6.72, 12.2, 0, "Start"},
		{4.5, 1.53, 6.72, 12.2, 1, "Quit"}, {.caption = NULL}};

	if (bt_tex == NULL)
		(bt_tex = IMG_Load(TEXTUTES_FOLDER"button.jpg")) == NULL
			? ft_err_handler(IMG_GetError(), NULL, 0, 1) : 0;
	SDL_ShowCursor(SDL_ENABLE);
	ft_bzero(screen->pixels, screen->w * screen->h * 4);
	Mix_PlayingMusic() == 0 ? Mix_PlayMusic(gd->menu_sound, -1) : 0;
	SDL_BlitScaled(gd->menu_bg, NULL, screen, NULL);
	sgl_draw_str("Wolf3D", &(t_font){"wolfenstein", screen->h / 3, 0xFFFFFF, 0},
				(t_point){screen->w / 8, screen->h / 12, 0}, screen);
	i = -1;
	while (bt[++i].caption)
	{
		SDL_BlitScaled(bt_tex, NULL, screen, &(SDL_Rect){screen->w / bt[i].x,
				screen->h / bt[i].y, screen->w / bt[i].w, screen->h / bt[i].h});
		sgl_draw_str(bt[i].caption, &(t_font){"wolfenstein", screen->h / 22,
				0xFFFFFF, 0}, (t_point){screen->w / (bt[i].x - 0.95),
					screen->h / (bt[i].y - 0.03 + i / 120.0), 0}, screen);
	}
}
