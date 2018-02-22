/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:19:10 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 01:28:30 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				death_cam_mouse(SDL_MouseButtonEvent e, t_game *gd)
{
	int			size[2];
	t_point		p;

	p.x = gd->screen->w / 2.2;
	p.y = gd->screen->h / 1.5;
	size[0] = p.x + gd->screen->w / 17 * 2.2;
	size[1] = p.y + gd->screen->w / 17 * 1.5;
	if (e.x >= p.x && e.x < size[0] && e.y >= p.y && e.y < size[1])
	{
		gd->state = 0;
		Mix_HaltMusic();
	}
}

void				death_cam(SDL_Surface *screen, t_game *gd)
{
	static SDL_Surface	*go;
	int					size[2];
	t_point				p;
	char				*buff;

	ft_bzero(screen->pixels, screen->w * screen->h * 4);
	if (!go && !(go = sgl_imgload(TEXTUTES_FOLDER"game_over.png")))
		ft_err_handler(IMG_GetError(), NULL, 0, 1);
	SDL_ShowCursor(SDL_ENABLE);
	size[0] = screen->w / 3;
	size[1] = screen->h / 6;
	p.x = (double)(screen->w - size[0]) / 2.0;
	p.y = (double)(screen->h - size[1]) / 2.0 - 100;
	SDL_BlitScaled(go, NULL, screen, &(SDL_Rect){p.x, p.y, size[0], size[1]});
	sgl_draw_str("Menu", &(t_font){"wolfenstein", screen->w / 17,
					0x8C0000, 0}, (t_point){screen->w / 2.2,
					screen->h / 1.5, 0}, screen);
	sgl_draw_str("Your score:", &(t_font){"wolfenstein", screen->w / 17,
					0xFFFFFF, 0}, (t_point){screen->w / 2.8,
					screen->h / 1.8, 0}, screen);
	buff = ft_itoa(gd->score);
	sgl_draw_str(buff, &(t_font){"wolfenstein", screen->w / 17,
					0xFFFFFF, 0}, (t_point){screen->w / 1.9,
					screen->h / 1.8, 0}, screen);
	free(buff);
}

inline static void	draw_console(t_game *gd)
{
	SDL_Rect		c_size;
	static t_font	c_font = {"SourceSans", 20, 0xAC00, 0};
	static t_font	font = {"SourceSans", 20, 0xFFFFFF, 0};

	c_size = sgl_str_size(&c_font, gd->command);
	SDL_FillRect(gd->screen, &(SDL_Rect){8, 38, 134 + c_size.w, 31}, 0xFFFFFF);
	SDL_FillRect(gd->screen, &(SDL_Rect){10, 40, 130 + c_size.w, 27}, 0x0);
	sgl_draw_str("Command $>", &font, (t_point){15, 40, 0}, gd->screen);
	sgl_draw_str(gd->command, &c_font, (t_point){130, 40, 0}, gd->screen);
	if (SDL_GetTicks() / 500 % 2 == 0)
		sgl_draw_str("|", &font, (t_point){130 + c_size.w, 38, 0}, gd->screen);
}

inline static void	ft_draw_stats(t_game *gd, int h)
{
	char	*bf;
	t_font	basic;

	basic = (t_font){"wolfenstein", gd->screen->w / 17, 0xFFFFFF, 0};
	bf = ft_itoa(gd->score);
	sgl_draw_str(bf, &basic, (t_point){30, gd->screen->h - h, 0}, gd->screen);
	free(bf);
	bf = ft_itoa(gd->health);
	sgl_draw_str(bf, &basic,
		(t_point){gd->screen->w / 1.6, gd->screen->h - h, 0}, gd->screen);
	free(bf);
	gd->key ? SDL_BlitScaled(gd->st_t[12],
		&(SDL_Rect){15, 50, 25, 10}, gd->screen,
		&(SDL_Rect){gd->screen->w / 2.85, gd->screen->h - h - 10,
			gd->screen->w / 10, h - 20}) : 0;
	gd->inputmode ? draw_console(gd) : 0;
	basic.size = gd->screen->w / 23;
	basic.color = 0xFFFF00;
	if (gd->godmode)
		sgl_draw_str("G", &basic, (t_point){gd->screen->w / 1.75,
						gd->screen->h - h - 30, 0}, gd->screen);
}

void				ft_draw_hud(t_game *gd)
{
	int					h;
	t_uint				ticks;

	h = gd->screen->w / 12;
	ticks = SDL_GetTicks();
	if (ticks - gd->shoot < 300)
		SDL_BlitScaled(gd->s_effect, NULL, gd->screen,
			&(SDL_Rect){gd->screen->w / 2 - gd->s_effect->w * 1.5,
			gd->screen->h - h - 300, gd->s_effect->w * 3, gd->s_effect->h * 3});
	SDL_BlitScaled(gd->weapon, NULL, gd->screen,
		&(SDL_Rect){gd->screen->w / 2 - gd->weapon->w,
			gd->screen->h - h + 30 - gd->weapon->h * 3,
			gd->weapon->w * 3, gd->weapon->h * 3});
	SDL_BlitScaled(gd->hud, NULL, gd->screen, &(SDL_Rect){0, gd->screen->h - h,
		gd->screen->w, h});
	h -= 15;
	SDL_BlitScaled(gd->f_t[ticks / 1000 % 4], NULL, gd->screen,
		&(SDL_Rect){gd->screen->w / 2.02, gd->screen->h - h - 7, h, h});
	ft_draw_stats(gd, h);
}
