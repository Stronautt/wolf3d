/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:19:10 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/12 15:32:29 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_draw_hud(t_game *gd)
{
	int		h;
	t_uint	ticks;
	char	*score_buff;

	h = gd->screen->w / 12;
	ticks = SDL_GetTicks();
	if (gd->shoot == SDL_GetTicks() / 1000)
		SDL_BlitScaled(gd->s_effect, NULL, gd->screen,
			&(SDL_Rect){gd->screen->w / 2 - gd->s_effect->w * 1.5,
			gd->screen->h - h - 300, gd->s_effect->w * 3, gd->s_effect->h * 3});
	SDL_BlitScaled(gd->weapon, NULL, gd->screen,
		&(SDL_Rect){gd->screen->w / 2 - gd->weapon->w,
			gd->screen->h - h + 30 - gd->weapon->h * 3,
			gd->weapon->w * 3, gd->weapon->h * 3});
	SDL_BlitScaled(gd->hud, NULL, gd->screen, &(SDL_Rect){0, gd->screen->h - h,
		gd->screen->w, h});
	h -= 20;
	ticks / 1000 % 2 ? gd->score++ : 0;
	SDL_BlitScaled(gd->f_t[ticks / 1000 % 4], NULL, gd->screen,
		&(SDL_Rect){gd->screen->w / 2.02, gd->screen->h - h - 10, h, h});
	score_buff = ft_itoa(gd->score);
	sgl_draw_str(score_buff, &(t_font){"wolfenstein", gd->screen->w / 17,
		0xFFFFFF, 0}, (t_point){gd->screen->w / 6.46, gd->screen->h - h, 0},
		gd->screen);
	free(score_buff);
}
