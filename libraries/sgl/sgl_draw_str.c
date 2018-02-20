/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:10:00 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_draw_str(char *string, t_font *font_data,
						t_point align, SDL_Surface *surface)
{
	SDL_Surface	*text_surf;

	if (!string || !*string || !(text_surf = sgl_text(font_data, string)))
		return ;
	SDL_BlitSurface(text_surf, NULL, surface,
					&(SDL_Rect){(int)align.x, (int)align.y, 0, 0});
}
