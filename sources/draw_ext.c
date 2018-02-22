/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:08:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 01:17:30 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_map(t_game *gd)
{
	int		c_size;
	t_point	p;
	t_point	offset;

	c_size = gd->screen->w / (4 * gd->map.h);
	offset = (t_point){gd->screen->w - gd->screen->w / 4, 10, 0};
	p = (t_point){-1, 0, 0};
	while (++p.x < gd->map.h && (p.y = -1))
		while (++p.y < gd->map.w)
			if (IS_WALL(gd->map.data[(int)p.y][(int)p.x]))
				SDL_FillRect(gd->screen, &(SDL_Rect){p.x * c_size + offset.x,
					p.y * c_size + offset.y, c_size, c_size}, 0xEFEFEF);
			else if (IS_SSPRITE(gd->map.data[(int)p.y][(int)p.x]))
				SDL_FillRect(gd->screen, &(SDL_Rect){p.x * c_size + offset.x,
					p.y * c_size + offset.y, c_size, c_size}, 0x8C);
			else if (SPRITE(gd->map.data[(int)p.y][(int)p.x]))
				SDL_FillRect(gd->screen, &(SDL_Rect){p.x * c_size + offset.x,
					p.y * c_size + offset.y, c_size, c_size}, 0x8C8C00);
			else
				SDL_FillRect(gd->screen, &(SDL_Rect){p.x * c_size + offset.x,
					p.y * c_size + offset.y, c_size, c_size}, 0);
	SDL_FillRect(gd->screen, &(SDL_Rect){gd->p_pos.y * c_size + offset.x -\
		c_size / 3, gd->p_pos.x * c_size + offset.y - c_size / 3, c_size / 1.5,
		c_size / 1.5}, 0x8C00);
}

void		draw_effects(t_game *gd)
{
	static SDL_Surface	*blood;
	static SDL_Surface	*hit;
	t_uint				ticks;

	if (!blood && !(blood = sgl_imgload(TEXTUTES_FOLDER"blood_effect.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if (!hit && !(hit = sgl_imgload(TEXTUTES_FOLDER"hit.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	ticks = SDL_GetTicks();
	gd->mapdisplay ? draw_map(gd) : 0;
	ticks - gd->mlg < MLG_DUR ? ft_mlg(gd) : ft_bzero(gd->mlg_m, 8);
	ticks - gd->mlg > MLG_DUR ? Mix_HaltChannel(MLG_CHANNEL) : 0;
	ticks - gd->heal < 200 ? sgl_apply_mask(gd->screen, 0xFF00) : 0;
	ticks - gd->key < 200 ? sgl_apply_mask(gd->screen, 0xFFFF00) : 0;
	ticks - gd->damage < 600 ? SDL_BlitScaled(blood, 0, gd->screen, 0) : 0;
	ticks - gd->hit < 250 ? SDL_BlitSurface(hit, 0, gd->screen, &(SDL_Rect)
		{(gd->screen->w - hit->w) / 2, (gd->screen->h - hit->h) / 2, 0, 0}) : 0;
}

static void	trace_enemy(t_game *gd, long cell, int *map)
{
	static	Mix_Music	*lose;
	int					dist;

	if (SPRITE(cell) != 5)
		return ;
	if (!lose && !(lose = Mix_LoadMUS(MUSIC_FOLDER"lose.mp3")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	dist = sqrt((gd->p_pos.x - map[0] - 0.5) * (gd->p_pos.x - map[0] - 0.5)
		+ (gd->p_pos.y - map[1] - 0.5) * (gd->p_pos.y - map[1] - 0.5));
	if (dist < 10 && SDL_GetTicks() - gd->damage > 2000)
	{
		if (!gd->godmode)
			gd->health = (gd->health - 8) > 100 ? 0 : gd->health - 8;
		gd->damage = SDL_GetTicks();
		Mix_PlayChannel(SHOOT_CHANNEL, gd->shoot_sound, 0);
		if (gd->health == 0)
		{
			gd->state = 3;
			gd->mlg = -MLG_DUR;
			Mix_HaltMusic();
			Mix_HaltChannel(MLG_CHANNEL);
			Mix_PlayMusic(lose, 0);
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
	s_width = ABS((int)(gd->screen->h / transf.y));
	t_d[0] = SPRITE(gd->map.data[map[0]][map[1]]) - 1;
	t_d[1] = (int)(256 * (map[2] - (-s_width / 2 + (gd->screen->w / 2) *
			(1 + transf.x / transf.y))) * gd->st_t[t_d[0]]->w / s_width) / 256;
	sgl_blit_line((SDL_Surface *[2]){gd->st_t[t_d[0]], gd->screen},
		(SDL_Rect){t_d[1], 0, 0, 0},
		(SDL_Rect){map[2], -s_width / 2 + gd->screen->h / 2, 0, s_width}
		, 0xFFFFFF);
	trace_enemy(gd, gd->map.data[map[0]][map[1]], map);
}
