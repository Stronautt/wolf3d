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

void	display_fps(SDL_Surface *surface)
{
	char			*fps_buff;
	static t_uint	frame_rate;
	t_uint			t_c;
	static t_uint	t_p;
	static t_uint	c_b;

	t_c = time(NULL);
	if (t_c - t_p && (t_p = t_c))
		frame_rate = 1000.0 / (SDL_GetTicks() - c_b);
	c_b = SDL_GetTicks();
	fps_buff = ft_itoa(frame_rate);
	sgl_draw_str("FPS: ", &(t_font){"SourceSans", 24, 0xFFFFFF, 0},
							(t_point){10, 5, 0}, surface);
	sgl_draw_str(fps_buff, &(t_font){"SourceSans", 24, 0xFFFFFF, 0},
							(t_point){60, 5, 0}, surface);
	ft_memdel((void **)&fps_buff);
}
