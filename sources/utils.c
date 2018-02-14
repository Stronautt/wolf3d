/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:49:38 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/14 00:40:15 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_game(t_game *gd)
{
	gd->dir.x = -1;
	gd->dir.y = 0;
	gd->plane.x = 0;
	gd->plane.y = 0.76;
	gd->mov_speed = 0.08;
	gd->rot_speed = 0.05;
	gd->move = 0;
	gd->rotate = 0;
	gd->state = 0;
	gd->score = 0;
	gd->shoot = 0;
}

void	reload_map(t_game *gd, int level)
{
	int		i;

	i = -1;
	while (++i < gd->map.w)
		ft_memdel((void **)&gd->map.data[i]);
	ft_memdel((void **)&gd->map.data);
	load_map(gd, level);
}

void	load_side_media(t_game *game)
{
	int			i;
	static char	face_t_name[] = TEXTUTES_FOLDER"face/face_0.png";

	i = -1;
	while (++i < 4)
	{
		face_t_name[ft_strlen(face_t_name) - 5] = i + '0';
		if (!(game->f_t[i] = IMG_Load(face_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
	}
	if (!(game->weapon = IMG_Load(TEXTUTES_FOLDER"weapon.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if (!(game->s_effect = IMG_Load(TEXTUTES_FOLDER"shoot_effect.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if ((game->shoot_sound = Mix_LoadWAV(MUSIC_FOLDER"shoot.mp3")) == NULL)
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
}

void	load_media(t_game *game)
{
	SDL_Surface	*tmp;
	int			i;
	char		symb;
	static char	wall_t_name[] = TEXTUTES_FOLDER"wall_1.jpg";
	static char	side_t_name[] = TEXTUTES_FOLDER"side_1.jpg";

	i = 0;
	while (++i < 16)
	{
		symb = (i + '0' <= '9') ? i + '0' : i - 10 + 'A';
		wall_t_name[ft_strlen(wall_t_name) - 5] = symb;
		side_t_name[ft_strlen(side_t_name) - 5] = symb;
		if (!(tmp = IMG_Load(wall_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
		game->w_t[i - 1] = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_FreeSurface(tmp);
		if (!(tmp = IMG_Load(side_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
		game->s_t[i - 1] = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
		SDL_FreeSurface(tmp);
	}
	if (!(game->menu_bg = IMG_Load(TEXTUTES_FOLDER"menu_background.jpg")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if (!(game->hud = IMG_Load(TEXTUTES_FOLDER"hud.jpg")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if ((game->menu_sound = Mix_LoadMUS(MUSIC_FOLDER"menu.mp3")) == NULL)
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if ((game->game_sound = Mix_LoadMUS(MUSIC_FOLDER"game.mp3")) == NULL)
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	load_side_media(game);
}
