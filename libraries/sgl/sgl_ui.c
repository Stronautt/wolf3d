/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_ui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:59:54 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 22:59:54 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static void	draw_mark(SDL_Surface *m, SDL_Surface *s, SDL_Rect r)
{
	int		h;

	h = r.h * 9 / 16;
	SDL_BlitSurfaceScaled(m, NULL, s, &(SDL_Rect){r.x - h * m->w / m->h
		- r.h / 6, r.y + r.h * 5 / 16, h * m->w / m->h, h},
		SDL_SCALEMODE_NEAREST);
}

static SDL_Rect	cell(t_ui *c, SDL_Rect r, int row, int i)
{
	return ((SDL_Rect){r.x + i % sgl_ui_cols(c) * r.w / sgl_ui_cols(c),
		r.y + (i / sgl_ui_cols(c) - c->scroll) * row, 0, row});
}

static void	draw_ctl(t_ui *c, SDL_Surface *s, SDL_Rect a, int hover)
{
	SDL_Rect	r;
	SDL_Surface	*t;
	t_font		f;

	r = sgl_ui_rect(c, a);
	c->type == SGL_BOX ? SDL_FillSurfaceRect(s, &r, c->color) : 0;
	c->img && *c->img ? SDL_BlitSurfaceScaled(*c->img,
		c->src.w ? &c->src : NULL, s, &r, SDL_SCALEMODE_NEAREST) : 0;
	hover && c->mark && *c->mark ? draw_mark(*c->mark, s, r) : 0;
	f = sgl_ui_font(c, a);
	if (!c->text || !(t = sgl_text(&f, c->text)))
		return ;
	sgl_draw_str(c->text, &f, (t_point){r.x + (r.w - t->w) / 2,
		r.y + (r.h - t->h) / 2, 0}, s);
}

static void	draw_list(t_ui *c, SDL_Surface *s, SDL_Rect a, int hover)
{
	SDL_Rect	r;
	t_font		f;
	int			row;
	int			lines;
	int			i;

	r = sgl_ui_rect(c, a);
	f = sgl_ui_font(c, a);
	row = sgl_ui_row(c, a);
	SDL_SetSurfaceClipRect(s, &(SDL_Rect){0, r.y, s->w, r.h});
	i = (int)c->scroll * sgl_ui_cols(c) - 1;
	while (c->items && c->items[++i] && cell(c, r, row, i).y < r.y + r.h)
		sgl_draw_str(c->items[i], &f, (t_point){cell(c, r, row, i).x,
			cell(c, r, row, i).y, 0}, s);
	if (hover >= 0 && c->mark && *c->mark)
		draw_mark(*c->mark, s, cell(c, r, row, hover));
	lines = (sgl_ui_len(c) + sgl_ui_cols(c) - 1) / sgl_ui_cols(c);
	if (lines * row > r.h)
		SDL_FillSurfaceRect(s, &(SDL_Rect){r.x + r.w - row / 8, r.y + r.h
			* c->scroll / lines, row / 8, r.h * r.h / (lines * row)},
			c->color);
	SDL_SetSurfaceClipRect(s, NULL);
}

void		sgl_ui_draw(t_ui *ui, SDL_Surface *s, SDL_Rect *area)
{
	SDL_Rect	a;
	SDL_FPoint	m;
	int			hit;
	int			item;
	int			i;

	a = area ? *area : (SDL_Rect){0, 0, s->w, s->h};
	SDL_GetMouseState(&m.x, &m.y);
	hit = sgl_ui_at(ui, a, m, &item);
	i = -1;
	while (ui[++i].type)
		ui[i].type == SGL_LIST ? draw_list(&ui[i], s, a, i == hit ? item : -1)
			: draw_ctl(&ui[i], s, a, i == hit);
}
