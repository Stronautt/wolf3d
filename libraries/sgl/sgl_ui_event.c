/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_ui_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:59:54 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 22:59:54 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static int	list_item(t_ui *c, SDL_Rect a, SDL_Rect r, SDL_FPoint p)
{
	int		i;

	i = floor((p.y - r.y) / sgl_ui_row(c, a) + c->scroll) * sgl_ui_cols(c)
		+ (int)(p.x - r.x) * sgl_ui_cols(c) / r.w;
	return (i >= 0 && i < sgl_ui_len(c) ? i : -1);
}

static void	list_scroll(t_ui *c, SDL_Rect a, float dy)
{
	int		k;

	k = sgl_ui_cols(c);
	c->scroll = fmax(0, fmin(c->scroll - dy, (sgl_ui_len(c) + k - 1) / k
		- (double)sgl_ui_rect(c, a).h / sgl_ui_row(c, a)));
}

int			sgl_ui_at(t_ui *ui, SDL_Rect a, SDL_FPoint p, int *item)
{
	SDL_Rect	r;
	int			row;
	int			i;

	i = -1;
	while (ui[++i].type)
	{
		if (ui[i].type != SGL_BUTTON && ui[i].type != SGL_LIST)
			continue ;
		r = sgl_ui_rect(&ui[i], a);
		if (!SDL_PointInRect(&(SDL_Point){p.x, p.y}, &r))
			continue ;
		row = ui[i].type == SGL_LIST ? list_item(&ui[i], a, r, p) : 0;
		if (row < 0)
			continue ;
		item ? *item = row : 0;
		return (i);
	}
	return (-1);
}

int			sgl_ui_event(t_ui *ui, SDL_Event *e, SDL_Surface *s, int *item)
{
	SDL_Rect	a;
	int			i;
	int			row;

	a = (SDL_Rect){0, 0, s->w, s->h};
	if (e->type == SDL_EVENT_MOUSE_WHEEL && (i = sgl_ui_at(ui, a,
		(SDL_FPoint){e->wheel.mouse_x, e->wheel.mouse_y}, &row)) >= 0
		&& ui[i].type == SGL_LIST)
		list_scroll(&ui[i], a, e->wheel.y);
	if (e->type != SDL_EVENT_MOUSE_BUTTON_DOWN
		|| e->button.button != SDL_BUTTON_LEFT)
		return (-1);
	return (sgl_ui_at(ui, a, (SDL_FPoint){e->button.x, e->button.y}, item));
}
