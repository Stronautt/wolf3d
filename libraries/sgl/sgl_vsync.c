/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_vsync.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:06:25 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 14:04:20 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static double	frame_ms(SDL_Window *win)
{
	const SDL_DisplayMode	*mode;

	mode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(win));
	return (mode && mode->refresh_rate > 0 ? 1000 / mode->refresh_rate : 17);
}

double			sgl_vsync(t_sgl_window *win)
{
	double			delay;
	double			target;
	Uint64			now;
	static Uint64	t_b;
	static int		soft_cap = -1;

	soft_cap < 0 ? soft_cap = !SDL_SetWindowSurfaceVSync(win->p, 1) : 0;
	target = frame_ms(win->p);
	!t_b ? t_b = SDL_GetTicksNS() - (Uint64)(target * 1e6) : 0;
	delay = (SDL_GetTicksNS() - t_b) / 1e6;
	if (soft_cap && delay < target)
		SDL_DelayPrecise((target - delay) * 1e6);
	now = SDL_GetTicksNS();
	delay = (now - t_b) / 1e6;
	t_b = now;
	return ((delay > 50 ? 50 : delay) / 17.0);
}
