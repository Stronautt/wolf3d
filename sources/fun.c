/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 14:44:01 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/19 21:02:23 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		item_actions(t_game *gd, long *cell, t_uint type)
{
	int		clear;

	clear = 0;
	type == 7 && gd->key ? reload_map(gd, IS_SSPRITE(*cell), 0) : 0;
	type == 3 && ++clear ? gd->mlg = SDL_GetTicks() : 0;
	type == 9 && ++clear ? gd->score += 275 * (1 - gd->godmode) : 0;
	type == 11 && ++clear ? (gd->health += 20)
			&& (gd->heal = SDL_GetTicks()) : 0;
	gd->health > 100 ? gd->health = 100 : 0;
	type == 13 && ++clear ? gd->key = SDL_GetTicks() : 0;
	clear ? EREASE_SPRITE(*cell) : 0;
}

void		expose_actions(t_game gd)
{
	t_uint	type;
	long	cell;

	if (gd.state != 2)
		return ;
	cell = gd.map.data[(int)gd.p_pos.x][(int)gd.p_pos.y];
	type = SPRITE(cell);
	type == 7 && !gd.key ? display_message(gd.screen, "First, find a key!") : 0;
}

void		shoot(t_game *gd)
{
	int					map[3];
	long				h;
	static SDL_Surface	*hit;

	gd->shoot = SDL_GetTicks();
	Mix_PlayChannel(SHOOT_CHANNEL, gd->shoot_sound, 0);
	ft_memcpy(map, (int[3]){gd->p_pos.x, gd->p_pos.y, gd->screen->w / 2}, 12);
	shoot_dda(map, gd);
	if (SPRITE(gd->map.data[map[0]][map[1]]) != 5)
		return ;
	gd->hit = gd->shoot;
	if (!hit && !(hit = sgl_imgload(TEXTUTES_FOLDER"hit.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	gd->score += 75 * (1 - gd->godmode);
	h = IS_SSPRITE(gd->map.data[map[0]][map[1]]) - 1;
	EREASE_SPRITE(gd->map.data[map[0]][map[1]]);
	h <= 0 ? (gd->score += 100 * (1 - gd->godmode))
			: (gd->map.data[map[0]][map[1]] |= (h << 28));
	gd->map.data[map[0]][map[1]] |= (h <= 0) ? (0x6L << 24) : (0x5L << 24);
}

static void	spawn_gold(t_game *gd)
{
	int		i;
	int		j;

	i = -1;
	while (++i < gd->map.w && (j = -1))
		while (++j < gd->map.h)
			if (!IS_WALL(gd->map.data[i][j]) && !SPRITE(gd->map.data[i][j])
				&& rand() % 17 == 0)
				gd->map.data[i][j] |= (0x9L << 24);
}

void		ft_mlg(t_game *gd)
{
	t_uint				it;
	static Mix_Chunk	*music;
	static t_uint		mlg_mask[] = {0x0000FF, 0x00FF00, 0xFF0000};

	if (!music && !(music = Mix_LoadWAV(MUSIC_FOLDER"mlg.mp3")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!Mix_Playing(MLG_CHANNEL) && !Mix_HaltMusic())
		spawn_gold(gd);
	!Mix_Playing(MLG_CHANNEL) ? Mix_PlayChannel(MLG_CHANNEL, music, 0) : 0;
	it = SDL_GetTicks() / 200 % (sizeof(mlg_mask) / sizeof(t_uint));
	gd->mlg_m[0] = mlg_mask[it];
	gd->mlg_m[1] = mlg_mask[(it + 1) % (sizeof(mlg_mask) / sizeof(t_uint))];
}
