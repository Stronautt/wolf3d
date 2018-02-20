/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:08:21 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static SDL_AtomicInt	g_aimed;

void		draw_effects(t_game *gd)
{
	static SDL_Surface	*blood;
	static SDL_Surface	*scaled;
	static SDL_Surface	*hit;
	t_uint				ticks;

	if (!blood && !(blood = sgl_imgload(TEXTUTES_FOLDER"blood_effect.png")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!hit && !(hit = sgl_imgload(TEXTUTES_FOLDER"hit.png")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!scaled || scaled->w != gd->screen->w || scaled->h != gd->screen->h)
	{
		SDL_DestroySurface(scaled);
		if (!(scaled = SDL_ScaleSurface(blood, gd->screen->w, gd->screen->h,
			SDL_SCALEMODE_NEAREST)))
			ft_err_handler(SDL_GetError(), NULL, 0, 1);
	}
	ticks = SDL_GetTicks();
	gd->mapdisplay ? draw_map(gd) : 0;
	ticks - gd->mlg < MLG_DUR ? ft_mlg(gd) : ft_bzero(gd->mlg_m, 8);
	ticks - gd->mlg > MLG_DUR ? sgl_halt(MLG_CHANNEL) : 0;
	ticks - gd->heal < 200 ? sgl_apply_mask(gd->screen, 0xFF00) : 0;
	ticks - gd->key < 200 ? sgl_apply_mask(gd->screen, 0xFFFF00) : 0;
	ticks - gd->damage < 600 ? SDL_BlitSurface(scaled, 0, gd->screen, 0) : 0;
	ticks - gd->hit < 250 ? SDL_BlitSurface(hit, 0, gd->screen, &(SDL_Rect)
		{(gd->screen->w - hit->w) / 2, (gd->screen->h - hit->h) / 2, 0, 0}) : 0;
}

static void	trace_enemy(t_game *gd, long cell, int *map, double centre)
{
	int		dist;

	if (SPRITE(cell) != 5
		|| map[2] != (int)fmin(fmax(centre, 0), gd->screen->w - 1))
		return ;
	dist = sqrt((gd->p_pos.x - map[0] - 0.5) * (gd->p_pos.x - map[0] - 0.5)
		+ (gd->p_pos.y - map[1] - 0.5) * (gd->p_pos.y - map[1] - 0.5));
	if (dist < 10 && SDL_GetTicks() - gd->damage > 1000)
		SDL_AddAtomicInt(&g_aimed, 1);
}

void		enemy_actions(t_game *gd)
{
	static	MIX_Audio	*lose;

	if (!lose && !(lose = MIX_LoadAudio(NULL, MUSIC_FOLDER"lose.mp3", 0)))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (rand() % 25391
		< SDL_SetAtomicInt(&g_aimed, 0) * ENEMY_AIM_WEIGHT * gd->dt)
	{
		if (!gd->godmode)
			gd->health = (gd->health - 8) > 100 ? 0 : gd->health - 8;
		gd->damage = SDL_GetTicks();
		sgl_play(SHOOT_CHANNEL, gd->shoot_sound, 0);
		if (gd->health == 0)
		{
			gd->state = 3;
			gd->mlg = -MLG_DUR;
			sgl_halt(MUSIC_CHANNEL);
			sgl_halt(MLG_CHANNEL);
			sgl_play(MUSIC_CHANNEL, lose, 0);
		}
	}
}

void		draw_sprite(t_game *gd, int *map)
{
	t_point	sprite;
	t_point	transf;
	double	inverse;
	int		s_width;
	int		t_d[2];

	sprite.x = map[0] + 0.5 - gd->p_pos.x;
	sprite.y = map[1] + 0.5 - gd->p_pos.y;
	inverse = 1.0 / (gd->plane.x * gd->dir.y - gd->dir.x * gd->plane.y);
	transf.x = inverse * (gd->dir.y * sprite.x - gd->dir.x * sprite.y);
	transf.y = inverse * (-gd->plane.y * sprite.x + gd->plane.x * sprite.y);
	if (transf.y < SPRITE_MIN_DEPTH
		|| !(s_width = ABS((int)(gd->screen->h / transf.y))))
		return ;
	t_d[0] = SPRITE(gd->map.data[map[0]][map[1]]) - 1;
	t_d[1] = (int)(256 * (map[2] - (-s_width / 2 + (gd->screen->w / 2) *
			(1 + transf.x / transf.y))) * gd->st_t[t_d[0]]->w / s_width) / 256;
	draw_column(gd->screen, map[2], (t_col){texel(gd->st_t[t_d[0]], t_d[1], 0),
		gd->st_t[t_d[0]]->pitch / 4, gd->st_t[t_d[0]]->h,
		-s_width / 2 + gd->screen->h / 2, s_width, 0xFFFFFF, 1});
	trace_enemy(gd, gd->map.data[map[0]][map[1]], map,
		(gd->screen->w / 2) * (1 + transf.x / transf.y));
}
