/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:49:38 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static char	g_mesg[128];

static t_ui	g_msg[] = {
	{SGL_BOX, 2.926, 2.418, 3.16, 5.76, .color = 0x0},
	{SGL_BOX, 2.9, 2.39, 3.22, 6.1, .color = 0xFFFFFF},
	{SGL_LABEL, 2.67, 2.287, 0, 0, g_mesg, "wolfenstein", 10.7, .color = 0x0},
	{0}};

void	init_game(t_game *gd)
{
	gd->dir.x = -1;
	gd->dir.y = 0;
	gd->plane.x = 0;
	gd->plane.y = 0.66;
	gd->mov_speed = WALK_SPEED;
	gd->rot_speed = WALK_ROT;
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
	int		h;

	h = screen->w * REF_H / REF_W;
	SDL_strlcpy(g_mesg, mesg, sizeof(g_mesg));
	sgl_ui_draw(g_msg, screen,
		&(SDL_Rect){0, (screen->h - h) / 2, screen->w, h});
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
			ft_err_handler(SDL_GetError(), NULL, 0, 1);
		if (!(game->st_t[i] = sgl_imgload(sprite_t_name)))
			ft_err_handler(SDL_GetError(), NULL, 0, 1);
	}
	if (!(game->weapon = sgl_imgload(TEXTUTES_FOLDER"weapon.png")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!(game->s_effect = sgl_imgload(TEXTUTES_FOLDER"shoot_effect.png")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!(game->shoot_sound = MIX_LoadAudio(NULL, MUSIC_FOLDER"shoot.mp3", 1)))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!(game->mlg_s = MIX_LoadAudio(NULL, MUSIC_FOLDER"mlg.mp3", 0)))
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
		if (!(game->w_t[i - 1] = load_wall(wall_t_name)))
			ft_err_handler(SDL_GetError(), NULL, 0, 1);
		if (!(game->s_t[i - 1] = sgl_imgload(side_t_name)))
			ft_err_handler(SDL_GetError(), NULL, 0, 1);
	}
	if (!(game->menu_bg = sgl_imgload(TEXTUTES_FOLDER"menu_background.jpg")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!(game->hud = sgl_imgload(TEXTUTES_FOLDER"hud.jpg")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!(game->menu_sound = MIX_LoadAudio(NULL, MUSIC_FOLDER"menu.mp3", 0)))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	if (!(game->game_sound = MIX_LoadAudio(NULL, MUSIC_FOLDER"game.mp3", 0)))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	load_side_media(game);
}
