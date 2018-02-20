/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_selector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:45:21 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static SDL_Surface	*g_cursor;

static t_ui			g_ui[] = {
	{SGL_LIST, 3.5, 1.75, 4.375, 4.1, NULL, "wolfenstein", 20, 0xFFFFFF,
		.mark = &g_cursor, .cols = 2},
	{SGL_LABEL, 5, 5, 0, 0, "Select level", "wolfenstein", 5,
		.color = 0xFFFFFF},
	{SGL_BUTTON, 3.5, 1.22, 0, 0, "Back", "wolfenstein", 20, 0xFFFFFF,
		.mark = &g_cursor},
	{0}};

static int	name_cmp(const void *a, const void *b)
{
	char	*s1;
	char	*s2;
	size_t	n1;
	size_t	n2;

	s1 = *(char **)a;
	s2 = *(char **)b;
	while (*s1 && *s1 == *s2 && !ft_isdigit(*s1))
	{
		s1++;
		s2++;
	}
	if (!ft_isdigit(*s1) || !ft_isdigit(*s2))
		return ((unsigned char)*s1 - (unsigned char)*s2);
	n1 = ft_skipdigits(s1);
	n2 = ft_skipdigits(s2);
	if (n1 != n2)
		return (n1 < n2 ? -1 : 1);
	if (ft_strncmp(s1, s2, n1))
		return (ft_strncmp(s1, s2, n1));
	return (name_cmp(&(char *){s1 + n1}, &(char *){s2 + n2}));
}

void		load_levels(t_game *gd)
{
	int		n;
	int		i;

	n = 0;
	SDL_free(g_ui->items);
	if (!(g_ui->items = SDL_GlobDirectory(MAPS_FOLDER, "*.map", 0, &n)) || !n)
		ft_err_handler(MAPS_FOLDER, g_ui->items ? "No maps found"
			: SDL_GetError(), 0, 0);
	i = -1;
	while (++i < n)
		g_ui->items[i][ft_strlen(g_ui->items[i]) - 4] = 0;
	SDL_qsort(g_ui->items, n, sizeof(char *), name_cmp);
	g_ui->scroll = 0;
	gd->state = 1;
}

void		level_selector_mouse(SDL_Event *e, t_game *gd)
{
	int		i;
	int		item;

	if ((i = sgl_ui_event(g_ui, e, gd->screen, &item)) >= 0)
	{
		if (g_ui[i].type != SGL_LIST && !(gd->state = 0))
			return ;
		reload_map(gd, g_ui[i].items[item], 1) ? sgl_halt(MUSIC_CHANNEL) : 0;
	}
}

void		ft_draw_levels(SDL_Surface *screen, t_game *gd)
{
	if (!g_cursor && !(g_cursor = sgl_imgload(TEXTUTES_FOLDER"cursor.png")))
		ft_err_handler(SDL_GetError(), NULL, 0, 1);
	sgl_playing(MUSIC_CHANNEL) || sgl_play(MUSIC_CHANNEL, gd->menu_sound, -1);
	SDL_BlitSurfaceScaled(gd->menu_bg, NULL, screen, NULL,
		SDL_SCALEMODE_NEAREST);
	sgl_ui_draw(g_ui, screen, NULL);
}
