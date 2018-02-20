/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:08:06 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_wlist	*g_win_list = NULL;
t_flist	*g_font_list = NULL;
t_uchar	g_rewrite_mode = 1;
MIX_Track	*g_tracks[SGL_TRACKS];

void	sgl_init(void)
{
	MIX_Mixer	*mixer;
	int			i;

	if (!SDL_Init(SDL_INIT_VIDEO))
		s_err_handler("SDL", SDL_GetError(), 0, 1);
	if (!TTF_Init())
		s_err_handler("SDL_TTF", SDL_GetError(), 0, 1);
	if (!MIX_Init())
		s_err_handler("SDL_MIX", SDL_GetError(), 0, 1);
	if (!(mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
										NULL)))
	{
		s_err_handler("SDL_MIX", SDL_GetError(), 0, 0);
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		SDL_SetHintWithPriority(SDL_HINT_AUDIO_DRIVER, "dummy",
								SDL_HINT_OVERRIDE);
		if (!(mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
											NULL)))
			s_err_handler("SDL_MIX", SDL_GetError(), 0, 1);
	}
	i = -1;
	while (++i < SGL_TRACKS)
		if (!(g_tracks[i] = MIX_CreateTrack(mixer)))
			s_err_handler("SDL_MIX", SDL_GetError(), 0, 1);
}
