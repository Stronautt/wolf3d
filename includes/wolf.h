/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 19:34:52 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/14 00:24:10 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include "sgl.h"
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <limits.h>
# include <pthread.h>
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_mixer.h"

# define PROGRAM_NAME "Wolf 3D"

# define TEXTUTES_FOLDER "./resources/textures/"
# define MUSIC_FOLDER "./resources/music/"

# define MAPS_FOLDER "./resources/maps/"
# define MAX_MAP_SIZE 1024

# define EXIT_KEY SDLK_ESCAPE

# define CL_MAX_SOURCE_SIZE 0x400000

# define THREADS 8

# define TOP_WALL(n)((n & 0xFL) - 1)
# define BOT_WALL(n)(((n & 0xF0L) >> 4) - 1)
# define LEFT_WALL(n)(((n & 0xF000L) >> 12) - 1)
# define RIGHT_WALL(n)(((n & 0xF00L) >> 8) - 1)

# define C_T(n)(((n & 0xF0000L) >> 16) - 1)
# define F_T(n)(((n & 0xF00000L) >> 20) - 1)

# define IS_WALL(n)(n & 0xFFFFL)

# define IS_PORTAL(n)((n & 0xF000000L) >> 24)

typedef t_dlist	t_wlist;

typedef struct	s_map
{
	int		w;
	int		h;
	long	**data;
}				t_map;

typedef struct	s_game
{
	t_point		p_pos;
	t_point		dir;
	t_point		plane;
	double		mov_speed;
	double		rot_speed;
	int			move;
	int			rotate;
	t_map		map;
	t_uchar		state;
	Mix_Music	*game_sound;
	Mix_Chunk	*shoot_sound;
	Mix_Music	*menu_sound;
	SDL_Surface *screen;
	SDL_Surface *hud;
	SDL_Surface *weapon;
	SDL_Surface *s_effect;
	SDL_Surface	*menu_bg;
	SDL_Surface	*w_t[16];
	SDL_Surface	*s_t[16];
	SDL_Surface	*f_t[4];
	int			score;
	int			shoot;
}				t_game;

typedef struct	s_draw
{
	int		*map;
	double	wall_x;
	int		y;
	int		h;
	int		w;
}				t_draw;

typedef struct	s_thread
{
	SDL_Surface *screen;
	t_game		gd;
	int			start;
	int			end;
}				t_thread;

typedef struct	s_button
{
	double	x;
	double	y;
	double	w;
	double	h;
	t_uchar	act;
	char	*caption;
}				t_button;

/*
**		Sys_handler.c
**		↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			ft_err_handler(const char *msg, const char *add,
								int err, t_uchar stop);

/*
**		Event.c
**		↓↓↓↓↓↓↓
*/

int				poll_event(t_game *game);

/*
**		Movement.c
**		↓↓↓↓↓↓↓↓↓↓
*/

void			move(t_game *game, double delta);

void			rotate(t_game *game, double delta);

/*
**		Fps.c
**		↓↓↓↓↓
*/

void			display_fps(SDL_Surface *surface);

/*
**		Draw_game.c
**		↓↓↓↓↓↓↓↓↓↓↓
*/

void			ft_draw_game(SDL_Surface *surface, t_game *game);

/*
**		Map.c
**		↓↓↓↓↓
*/

void			load_map(t_game *game, int level);

/*
**		Menu.c
**		↓↓↓↓↓↓
*/

void			menu_mouse(SDL_MouseButtonEvent e, t_game *gd);

void			ft_draw_menu(SDL_Surface *surface, t_game *gd);

/*
**		Menu.c
**		↓↓↓↓↓↓
*/

void			level_selector_mouse(SDL_MouseButtonEvent e, t_game *gd);

void			level_selector_mouse_hover(t_game gd);

void			ft_draw_levels(SDL_Surface *screen, t_game *gd);

/*
**		Hud.c
**		↓↓↓↓↓↓
*/

void			ft_draw_hud(t_game *gd);

/*
**		Utils.c
**		↓↓↓↓↓↓↓
*/

void			init_game(t_game *gd);

void			reload_map(t_game *gd, int level);

void			load_media(t_game *game);

#endif
