/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:49:38 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/20 14:51:39 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_game(t_game *gd)
{
	gd->dir.x = -1;
	gd->dir.y = 0;
	gd->plane.x = 0;
	gd->plane.y = 0.66;
	gd->mov_speed = 0.08;
	gd->rot_speed = 0.05;
	gd->move = 0;
	gd->godmode = 0;
	gd->rotate = 0;
	gd->state = 0;
	gd->score = 0;
	gd->shoot = 0;
	gd->health = 50;
	gd->damage = -MLG_DUR;
	gd->heal = 0;
	gd->key = 0;
	gd->mlg = -MLG_DUR;
	gd->inputmode = 0;
	gd->mapdisplay = 0;
	ft_bzero(gd->command, sizeof(gd->command));
	ft_bzero(&gd->map, sizeof(gd->map));
}

void	display_message(SDL_Surface *screen, char *mesg)
{
	int		width;
	int		height;
	t_point	p;

	width = ft_strlen(mesg) * screen->w / 58 + 10;
	height = screen->w / 11 + 20 + 10;
	p.x = (screen->w - width) / 2;
	p.y = (screen->h - height) / 2;
	SDL_FillRect(screen, &(SDL_Rect){p.x, p.y, width, height}, 0x0);
	height -= 10;
	width -= 10;
	p.x = (screen->w - width) / 2;
	p.y = (screen->h - height) / 2;
	SDL_FillRect(screen, &(SDL_Rect){p.x, p.y, width, height}, 0xFFFFFF);
	sgl_draw_str(mesg, &(t_font){"wolfenstein", screen->w / 17,
		0x0, 0}, (t_point){p.x + 50, p.y + 20, 0}, screen);
}

void	reload_map(t_game *gd, int level, int pure)
{
	int		i;
	int		score;
	int		health;

	i = -1;
	while (++i < gd->map.w)
		ft_memdel((void **)&gd->map.data[i]);
	ft_memdel((void **)&gd->map.data);
	score = gd->score;
	health = gd->health;
	init_game(gd);
	gd->state = 2;
	!pure ? gd->score = score : 0;
	!pure ? gd->health = health : 0;
	load_map(gd, level);
}

void	load_side_media(t_game *game)
{
	int			i;
	static char	face_t_name[] = TEXTUTES_FOLDER"face/face_0.png";
	static char	sprite_t_name[] = TEXTUTES_FOLDER"sprite_1.png";

	i = -1;
	while (++i < 15)
	{
		face_t_name[ft_strlen(face_t_name) - 5] = i + '0';
		sprite_t_name[ft_strlen(sprite_t_name) - 5] = (i + 1 + '0' <= '9')
											? i + 1 + '0' : i + 1 - 10 + 'A';
		if (i < 4 && !(game->f_t[i] = sgl_imgload(face_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
		if (!(game->st_t[i] = sgl_imgload(sprite_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
	}
	if (!(game->weapon = sgl_imgload(TEXTUTES_FOLDER"weapon.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if (!(game->s_effect = sgl_imgload(TEXTUTES_FOLDER"shoot_effect.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if ((game->shoot_sound = Mix_LoadWAV(MUSIC_FOLDER"shoot.mp3")) == NULL)
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
}

void	load_media(t_game *game)
{
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
		if (!(game->w_t[i - 1] = sgl_imgload(wall_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
		if (!(game->s_t[i - 1] = sgl_imgload(side_t_name)))
			ft_err_handler(IMG_GetError(), NULL, 0, 1);
	}
	if (!(game->menu_bg = sgl_imgload(TEXTUTES_FOLDER"menu_background.jpg")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if (!(game->hud = sgl_imgload(TEXTUTES_FOLDER"hud.jpg")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	if ((game->menu_sound = Mix_LoadMUS(MUSIC_FOLDER"menu.mp3")) == NULL)
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if ((game->game_sound = Mix_LoadMUS(MUSIC_FOLDER"game.mp3")) == NULL)
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	load_side_media(game);
}
