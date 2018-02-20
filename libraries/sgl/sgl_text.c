/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 19:51:25 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 19:51:25 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static t_text		g_text[SGL_TEXT_SLOTS];

static int			text_eq(t_text *t, TTF_Font *font, t_uint color, char *s)
{
	return (t->str && t->ttf == font && t->color == color
		&& !ft_strcmp(t->str, s));
}

static SDL_Surface	*text_render(TTF_Font *font, t_font *font_data,
									char *string)
{
	SDL_Color	color;

	color = (SDL_Color){.r = font_data->color / 0x10000 % 256,
						.g = font_data->color / 0x100 % 256,
						.b = font_data->color % 256,
						.a = font_data->color / 0x1000000 % 256};
	return (TTF_RenderText_Blended(font, string, 0, color));
}

SDL_Surface			*sgl_text(t_font *font_data, char *string)
{
	static int	next;
	TTF_Font	*font;
	t_text		*t;
	int			i;

	if (!(font = sgl_get_font(font_data)))
		return (NULL);
	i = -1;
	while (++i < SGL_TEXT_SLOTS)
		if (text_eq(&g_text[i], font, font_data->color, string))
			return (g_text[i].surf);
	t = &g_text[next];
	next = (next + 1) % SGL_TEXT_SLOTS;
	SDL_DestroySurface(t->surf);
	free(t->str);
	*t = (t_text){font, font_data->color, ft_strdup(string),
		text_render(font, font_data, string)};
	return (t->surf);
}

void				sgl_text_flush(void)
{
	int		i;

	i = -1;
	while (++i < SGL_TEXT_SLOTS)
	{
		SDL_DestroySurface(g_text[i].surf);
		free(g_text[i].str);
	}
	ft_bzero(g_text, sizeof(g_text));
}
