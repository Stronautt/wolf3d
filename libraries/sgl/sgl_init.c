/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:08:06 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 01:07:28 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_wlist	*g_win_list = NULL;
t_flist	*g_font_list = NULL;
t_uchar	g_rewrite_mode = 1;

void	sgl_init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		s_err_handler("SDL", SDL_GetError(), 0, 1);
	if (TTF_Init() < 0)
		s_err_handler("SDL_TTF", TTF_GetError(), 0, 1);
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
		s_err_handler("SDL_IMG", IMG_GetError(), 0, 1);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		s_err_handler("SDL_IMG", SDL_GetError(), 0, 1);
}
