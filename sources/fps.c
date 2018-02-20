/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 20:05:02 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/02 17:32:05 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static char	g_fps[12];

static t_ui	g_ui[] = {
	{SGL_LABEL, 168, 210, 0, 0, "FPS: ", "SourceSans", 43.75,
		.color = 0xFFFFFF},
	{SGL_LABEL, 28, 210, 0, 0, g_fps, "SourceSans", 43.75, .color = 0xFFFFFF},
	{0}};

void	display_fps(SDL_Surface *surface, int show)
{
	static t_uint	frame_rate;
	t_uint			t_c;
	static t_uint	t_p;
	static t_uint	c_b;

	t_c = time(NULL);
	if (t_c - t_p && (t_p = t_c) && SDL_GetTicks() - c_b)
		frame_rate = 1000.0 / (SDL_GetTicks() - c_b);
	c_b = SDL_GetTicks();
	SDL_snprintf(g_fps, sizeof(g_fps), "%u", frame_rate);
	show ? sgl_ui_draw(g_ui, surface, &(SDL_Rect){0, 0, REF_W, REF_H}) : 0;
}
