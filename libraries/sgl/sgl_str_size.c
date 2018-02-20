/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_str_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 14:20:55 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

SDL_Rect	sgl_str_size(t_font *font_data, char *string)
{
	SDL_Rect	ret;
	TTF_Font	*font;

	ft_bzero(&ret, sizeof(ret));
	if (!(font = sgl_get_font(font_data)))
		return (ret);
	TTF_GetStringSize(font, string, 0, &ret.w, &ret.h);
	return (ret);
}
