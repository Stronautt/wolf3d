/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_play.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 13:44:50 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

bool	sgl_play(int track, MIX_Audio *audio, int loops)
{
	SDL_PropertiesID	opts;
	bool				ret;

	opts = SDL_CreateProperties();
	SDL_SetNumberProperty(opts, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
	ret = MIX_SetTrackAudio(g_tracks[track], audio)
		&& MIX_PlayTrack(g_tracks[track], opts);
	SDL_DestroyProperties(opts);
	return (ret);
}

bool	sgl_playing(int track)
{
	return (MIX_TrackPlaying(g_tracks[track]));
}

bool	sgl_halt(int track)
{
	return (MIX_StopTrack(g_tracks[track], 0));
}
