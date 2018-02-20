/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:31:29 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Simple Graphics Library
**	Copyright (C) 2018  Pavlo Gritsenko
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SGL_H
# define SGL_H

# include "libft.h"
# include <SDL3/SDL.h>
# include <SDL3_ttf/SDL_ttf.h>
# include <SDL3_image/SDL_image.h>
# include <SDL3_mixer/SDL_mixer.h>

# define ICON_PATH "./resources/images/icon.png"
# define FONT_PATH "./resources/fonts/"

# define SGL_TRACKS 8

# define SGL_LABEL 1
# define SGL_BUTTON 2
# define SGL_LIST 3
# define SGL_BOX 4

typedef struct	s_font
{
	char		*name;
	int			size;
	t_uint		color;
	TTF_Font	*ttf;
}				t_font;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct	s_rotate
{
	double	rx;
	double	ry;
	double	rz;
}				t_rotate;

typedef struct	s_window
{
	int				width;
	int				height;
	char			*title;
	t_uint			id;
	SDL_Window		*p;
	SDL_Surface		*surface;
}				t_sgl_window;

typedef struct	s_ui
{
	int			type;
	double		x;
	double		y;
	double		w;
	double		h;
	char		*text;
	char		*font;
	double		size;
	t_uint		color;
	SDL_Surface	**img;
	SDL_Rect	src;
	SDL_Surface	**mark;
	int			act;
	char		**items;
	int			cols;
	double		scroll;
}				t_ui;

void			sgl_init(void);

int				sgl_quit(void);

void			sgl_plot(t_point p, t_uint color, SDL_Surface *surface);

void			sgl_plot_m(t_point p, t_uint color,
							SDL_Surface *surface, t_uint mask);

void			sgl_fix_point(t_point *p, SDL_Surface *surface);

t_uint			sgl_get(SDL_Surface *surface, int x, int y);

void			sgl_draw_line(t_point a, t_point b, t_uint color,
								SDL_Surface *surface);

void			sgl_draw_str(char *string, t_font *font_data,
								t_point align, SDL_Surface *surface);

SDL_Rect		sgl_str_size(t_font *font_data, char *string);

t_sgl_window	*sgl_new_window(char *title, int width, int height, t_uint wm);

SDL_Surface		*sgl_resize_window(t_uint wind_id, int new_width,
												int new_height);

t_sgl_window	*sgl_get_window(char *title);

t_sgl_window	*sgl_get_window_by_id(t_uint id);

TTF_Font		*sgl_get_font(t_font *font_data);

void			sgl_blit_line(SDL_Surface *sur[2], SDL_Rect src_r,
								SDL_Rect dst_r, t_uint mask);

void			sgl_apply_mask(SDL_Surface *surf, t_uint mask);

double			sgl_vsync(t_sgl_window *win);

void			sgl_update_window(t_sgl_window *win);

bool			sgl_play(int track, MIX_Audio *audio, int loops);

bool			sgl_playing(int track);

bool			sgl_halt(int track);

void			sgl_rewite(t_uchar mode);

SDL_Surface		*sgl_imgload(char *path);

SDL_Surface		*sgl_text(t_font *font_data, char *string);

void			sgl_text_flush(void);

void			sgl_ui_draw(t_ui *ui, SDL_Surface *s, SDL_Rect *area);

int				sgl_ui_event(t_ui *ui, SDL_Event *e, SDL_Surface *s, int *item);

#endif
