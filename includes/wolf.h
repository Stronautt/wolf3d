/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 19:34:52 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
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

# define PROGRAM_NAME "Wolf 3D"

# define TEXTUTES_FOLDER "./resources/textures/"
# define MUSIC_FOLDER "./resources/music/"

# define MAPS_FOLDER "./resources/maps/"
# define MAX_MAP_SIZE 1024

# define MIN_WALL_DIST 1e-4

# define SPRITES_PER_RAY 64

# define SPRITE_MIN_DEPTH 0.01

# define ENEMY_AIM_WEIGHT 509

# define HUD_H(s) ((s)->w / 12)

# define REF_W 1680
# define REF_H 1050

# define EXIT_KEY SDLK_ESCAPE

# define WALK_SPEED 0.08
# define WALK_ROT 0.05
# define RUN_SPEED 0.13
# define RUN_ROT 0.07

# define RENDER_CHUNK 16

# if defined(__EMSCRIPTEN__) && !defined(__EMSCRIPTEN_PTHREADS__)
#  define RENDER_MAX_THREADS 1
# elif defined(SDL_PLATFORM_ANDROID) || defined(SDL_PLATFORM_IOS)
#  define RENDER_MAX_THREADS 4
# else
#  define RENDER_MAX_THREADS 32
# endif

# ifdef _WIN32
#  define ERR_BOX(t, m) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, m, 0)
# else
#  define ERR_BOX(t, m) 0
# endif

# define MLG_DUR 25000

# define SHOOT_CHANNEL 0

# define MLG_CHANNEL 1

# define MUSIC_CHANNEL 2

# define TOP_WALL(n)((n & 0xFL) - 1)
# define BOT_WALL(n)(((n & 0xF0L) >> 4) - 1)
# define LEFT_WALL(n)(((n & 0xF000L) >> 12) - 1)
# define RIGHT_WALL(n)(((n & 0xF00L) >> 8) - 1)

# define C_T(n)(((n & 0xF0000L) >> 16) - 1)
# define F_T(n)(((n & 0xF00000L) >> 20) - 1)

# define IS_WALL(n)(n & 0xFFFFL)

# define SPRITE(n)((n & 0xF000000L) >> 24)
# define IS_SSPRITE(n)((n & 0xF0000000L) >> 28)
# define EREASE_SPRITE(n)(n &= 0xFFFFFFFF00FFFFFFL)

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
	float		mov_speed;
	float		rot_speed;
	double		dt;
	char		move;
	char		rotate;
	t_map		map;
	t_uchar		state;
	MIX_Audio	*game_sound;
	MIX_Audio	*shoot_sound;
	MIX_Audio	*mlg_s;
	MIX_Audio	*menu_sound;
	SDL_Surface *screen;
	SDL_Surface *hud;
	SDL_Surface *weapon;
	SDL_Surface *s_effect;
	SDL_Surface	*menu_bg;
	SDL_Surface	*w_t[16];
	SDL_Surface	*s_t[16];
	SDL_Surface	*st_t[16];
	SDL_Surface	*f_t[4];
	int			score;
	char		command[128];
	t_uchar		inputmode;
	t_uchar		mapdisplay;
	t_uchar		fpsdisplay;
	t_uchar		godmode;
	t_uint		damage;
	t_uint		heal;
	t_uint		health;
	t_uint		shoot;
	t_uint		hit;
	t_uint		key;
	t_uint		mlg;
	t_uint		mlg_m[2];
}				t_game;

typedef struct	s_draw
{
	int		*map;
	double	wall_x;
	int		y;
	int		h;
}				t_draw;

typedef struct	s_col
{
	t_uint	*src;
	int		step;
	int		src_h;
	int		y;
	int		h;
	t_uint	mask;
	char	sprite;
}				t_col;

typedef struct	s_spr
{
	int		n;
	int		cell[SPRITES_PER_RAY][3];
}				t_spr;

typedef struct	s_dda
{
	t_point	step;
	t_point	delta;
	t_point	sd_dist;
}				t_dda;

typedef struct	s_pool
{
	SDL_Thread		*th[RENDER_MAX_THREADS];
	SDL_Semaphore	*go;
	SDL_Semaphore	*done;
	SDL_AtomicInt	next;
	t_game			*gd;
	int				n;
	int				quit;
}				t_pool;

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

void			shoot_dda(int *map, t_game *gd);

void			dda_init(t_game *gd, t_point *r_dir, int *map, t_dda *d);

/*
**		Fps.c
**		↓↓↓↓↓
*/

void			display_fps(SDL_Surface *surface, int show);

/*
**		Draw.c
**		↓↓↓↓↓↓
*/

void			ft_draw_heart(t_game *gd, SDL_AtomicInt *next);

void			ft_draw_game(SDL_Surface *surface, t_game *game);

/*
**		Pool.c
**		↓↓↓↓↓↓
*/

void			render_frame(t_game *gd);

void			render_quit(void);

/*
**		Draw_ext.c
**		↓↓↓↓↓↓↓↓↓↓
*/

void			draw_effects(t_game *gd);

void			draw_sprite(t_game *gd, int *map);

void			enemy_actions(t_game *gd);

/*
**		Minimap.c
**		↓↓↓↓↓↓↓↓↓
*/

void			draw_map(t_game *gd);

/*
**		Column.c
**		↓↓↓↓↓↓↓↓
*/

t_uint			*texel(SDL_Surface *s, int x, int y);

void			draw_column(SDL_Surface *dst, int x, t_col c);

void			ft_draw_floor_ceil(t_game *gd, double wall_dist, t_point r_d,
								t_draw d);

/*
**		Textures.c
**		↓↓↓↓↓↓↓↓↓↓
*/

SDL_Surface		*load_wall(char *path);

/*
**		Map.c
**		↓↓↓↓↓
*/

int				load_map(t_game *game, char *name);

/*
**		Level.c
**		↓↓↓↓↓↓↓
*/

void			free_map(t_map *map);

int				alloc_map(t_map *map, int rows, int cols);

int				rest_is_blank(int fd);

int				reload_map(t_game *gd, char *name, int pure);

/*
**		Menu.c
**		↓↓↓↓↓↓
*/

void			menu_mouse(SDL_Event *e, t_game *gd);

void			ft_draw_menu(SDL_Surface *surface, t_game *gd);

/*
**		Menu.c
**		↓↓↓↓↓↓
*/

void			load_levels(t_game *gd);

void			level_selector_mouse(SDL_Event *e, t_game *gd);

void			ft_draw_levels(SDL_Surface *screen, t_game *gd);

/*
**		Hud.c
**		↓↓↓↓↓↓
*/

void			death_cam_mouse(SDL_Event *e, t_game *gd);

void			death_cam(SDL_Surface *screen, t_game *gd);

void			ft_draw_hud(t_game *gd);

/*
**		Utils.c
**		↓↓↓↓↓↓↓
*/

void			init_game(t_game *gd);

void			display_message(SDL_Surface *screen, char *mesg);

void			load_media(t_game *game);

/*
**		Fun.c
**		↓↓↓↓↓
*/

void			item_actions(t_game *gd, long *cell, t_uint type);

void			expose_actions(t_game *gd);

void			shoot(t_game *gd);

void			ft_mlg(t_game *gd);

#endif
