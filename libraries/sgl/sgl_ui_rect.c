/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_ui_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:59:54 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 22:59:54 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_font		sgl_ui_font(t_ui *c, SDL_Rect a)
{
	return ((t_font){c->font, c->size ? a.h / c->size : 0, c->color, 0});
}

SDL_Rect	sgl_ui_rect(t_ui *c, SDL_Rect a)
{
	SDL_Rect	r;
	SDL_Surface	*t;
	t_font		f;

	f = sgl_ui_font(c, a);
	r = (SDL_Rect){0, 0, 0, 0};
	if (c->w && c->h)
		r = (SDL_Rect){0, 0, a.w / c->w, a.h / c->h};
	else if (c->text && (t = sgl_text(&f, c->text)))
		r = (SDL_Rect){0, 0, t->w, t->h};
	r.x = a.x + (c->x ? a.w / c->x : 0);
	r.y = a.y + (c->y ? a.h / c->y : 0);
	return (r);
}

int			sgl_ui_row(t_ui *c, SDL_Rect a)
{
	t_font	f;
	int		h;

	f = sgl_ui_font(c, a);
	h = TTF_GetFontHeight(sgl_get_font(&f));
	return (h > 0 ? h : 1);
}

int			sgl_ui_len(t_ui *c)
{
	int		n;

	n = 0;
	while (c->items && c->items[n])
		n++;
	return (n);
}

int			sgl_ui_cols(t_ui *c)
{
	return (c->cols > 1 ? c->cols : 1);
}
