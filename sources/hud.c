/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:19:10 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static SDL_Surface	*g_go;
static char			g_score[32];
static SDL_Surface	*g_bar;
static SDL_Surface	*g_face;
static SDL_Surface	*g_key;
static char			g_stat[2][12];
static char			g_god[2];
static char			g_cmd[130];

static t_ui			g_death[] = {
	{SGL_LABEL, 3, 3.115, 3, 6, .img = &g_go},
	{SGL_BUTTON, 2.2, 1.5, 0, 0, "Menu", "wolfenstein", 10.7,
		.color = 0x8C0000},
	{SGL_LABEL, 2.8, 1.8, 0, 0, g_score, "wolfenstein", 10.7,
		.color = 0xFFFFFF},
	{0}};

static t_ui			g_hud[] = {
	{SGL_LABEL, 0, 0, 1, 1, .img = &g_bar},
	{SGL_LABEL, 2.02, 14, 14, 1.166, .img = &g_face},
	{SGL_LABEL, 33.5, 7, 0, 0, g_stat[0], "wolfenstein", 1.417,
		.color = 0xFFFFFF},
	{SGL_LABEL, 1.6, 7, 0, 0, g_stat[1], "wolfenstein", 1.417,
		.color = 0xFFFFFF},
	{SGL_LABEL, 2.85, 14, 10, 1.647, .img = &g_key, .src = {15, 50, 25, 10}},
	{SGL_LABEL, 1.75, -7, 0, 0, g_god, "wolfenstein", 1.917,
		.color = 0xFFFF00},
	{0}};

static t_ui			g_console[] = {
	{SGL_BOX, 210, 27.63, 4.199, 33.87, .color = 0xFFFFFF},
	{SGL_BOX, 168, 26.25, 4.242, 38.88, .color = 0x0},
	{SGL_LABEL, 112, 26.25, 0, 0, "Command $>", "SourceSans", 52.5,
		.color = 0xFFFFFF},
	{SGL_LABEL, 12.92, 26.25, 0, 0, g_cmd, "SourceSans", 52.5,
		.color = 0xAC00},
	{0}};

void				death_cam_mouse(SDL_Event *e, t_game *gd)
{
	if (sgl_ui_event(g_death, e, gd->screen, NULL) >= 0)
	{
		gd->state = 0;
		sgl_halt(MUSIC_CHANNEL);
	}
}

void				death_cam(SDL_Surface *screen, t_game *gd)
{
	ft_bzero(screen->pixels, screen->w * screen->h * 4);
	if (!g_go && !(g_go = sgl_imgload(TEXTUTES_FOLDER"game_over.png")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	SDL_snprintf(g_score, sizeof(g_score), "Your score: %d", gd->score);
	sgl_ui_draw(g_death, screen, NULL);
}

inline static void	draw_console(t_game *gd)
{
	SDL_snprintf(g_cmd, sizeof(g_cmd), "%s%s", gd->command,
		SDL_GetTicks() / 500 % 2 ? "" : "|");
	sgl_ui_draw(g_console, gd->screen, &(SDL_Rect){0, 0, REF_W, REF_H});
}

inline static void	ft_draw_stats(t_game *gd)
{
	SDL_Surface	*s;

	s = gd->screen;
	g_bar = gd->hud;
	g_face = gd->f_t[SDL_GetTicks() / 1000 % 4];
	g_key = gd->key ? gd->st_t[12] : NULL;
	SDL_snprintf(g_stat[0], sizeof(g_stat[0]), "%d", gd->score);
	SDL_snprintf(g_stat[1], sizeof(g_stat[1]), "%u", gd->health);
	g_god[0] = gd->godmode ? 'G' : 0;
	sgl_ui_draw(g_hud, s, &(SDL_Rect){0, s->h - HUD_H(s), s->w, HUD_H(s)});
	gd->inputmode ? draw_console(gd) : 0;
}

void				ft_draw_hud(t_game *gd)
{
	int					h;
	t_uint				ticks;

	h = HUD_H(gd->screen);
	ticks = SDL_GetTicks();
	if (ticks - gd->shoot < 300)
		SDL_BlitSurfaceScaled(gd->s_effect, NULL, gd->screen,
			&(SDL_Rect){gd->screen->w / 2 - gd->s_effect->w * 1.5,
			gd->screen->h - h - 300, gd->s_effect->w * 3, gd->s_effect->h * 3},
			SDL_SCALEMODE_NEAREST);
	SDL_BlitSurfaceScaled(gd->weapon, NULL, gd->screen,
		&(SDL_Rect){gd->screen->w / 2 - gd->weapon->w,
			gd->screen->h - h + 30 - gd->weapon->h * 3,
			gd->weapon->w * 3, gd->weapon->h * 3}, SDL_SCALEMODE_NEAREST);
	ft_draw_stats(gd);
}
