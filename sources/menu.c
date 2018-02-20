/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:02:21 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static SDL_Surface	*g_bt_tex;

static t_ui			g_ui[] = {
	{SGL_LABEL, 8, 12, 0, 0, "Wolf3D", "wolfenstein", 3, .color = 0xFFFFFF},
	{SGL_BUTTON, 4.5, 1.75, 6.72, 12.2, "Start", "wolfenstein", 22, 0xFFFFFF,
		.img = &g_bt_tex},
	{SGL_BUTTON, 4.5, 1.53, 6.72, 12.2, "Quit", "wolfenstein", 22, 0xFFFFFF,
		.img = &g_bt_tex, .act = 1},
	{0}};

void	menu_mouse(SDL_Event *e, t_game *gd)
{
	int						i;

	if ((i = sgl_ui_event(g_ui, e, gd->screen, NULL)) >= 0)
		g_ui[i].act == 1 ? SDL_PushEvent(&(SDL_Event){SDL_EVENT_QUIT})
			: load_levels(gd);
}

void	ft_draw_menu(SDL_Surface *screen, t_game *gd)
{
	if (g_bt_tex == NULL)
		(g_bt_tex = sgl_imgload(TEXTUTES_FOLDER"button.jpg")) == NULL
			? ft_err_handler(SDL_GetError(), NULL, 0, 1) : 0;
	sgl_playing(MUSIC_CHANNEL) || sgl_play(MUSIC_CHANNEL, gd->menu_sound, -1);
	SDL_BlitSurfaceScaled(gd->menu_bg, NULL, screen, NULL,
		SDL_SCALEMODE_NEAREST);
	sgl_ui_draw(g_ui, screen, NULL);
}
