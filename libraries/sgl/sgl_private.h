/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:59:36 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SGL_PRIVATE_H
# define SGL_PRIVATE_H

# include "sgl.h"
# include <math.h>
# include <errno.h>

# define SGL_FORMAT SDL_PIXELFORMAT_XRGB8888

# define SGL_TEXT_SLOTS 32

typedef t_dlist	t_wlist;
typedef t_dlist	t_flist;

extern t_wlist	*g_win_list;
extern t_flist	*g_font_list;

extern t_uchar	g_rewrite_mode;

extern MIX_Track	*g_tracks[SGL_TRACKS];

typedef struct	s_text
{
	TTF_Font	*ttf;
	t_uint		color;
	char		*str;
	SDL_Surface	*surf;
}				t_text;

TTF_Font		*sgl_add_font(t_font *font_data);

void			destroy_fonts(void);

void			s_err_handler(const char *msg, const char *add,
								int err, t_uchar stop);

t_font			sgl_ui_font(t_ui *c, SDL_Rect a);

SDL_Rect		sgl_ui_rect(t_ui *c, SDL_Rect a);

int				sgl_ui_row(t_ui *c, SDL_Rect a);

int				sgl_ui_len(t_ui *c);

int				sgl_ui_cols(t_ui *c);

int				sgl_ui_at(t_ui *ui, SDL_Rect a, SDL_FPoint p, int *item);

#endif
