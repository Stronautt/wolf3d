/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/09 17:19:56 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

inline static void	destroy_wins(void)
{
	t_wlist			*win;
	t_wlist			*next;
	t_sgl_window	*tmp;

	if (!g_win_list)
		return ;
	win = g_win_list;
	next = win->next;
	while ((win = next) != g_win_list)
	{
		tmp = win->content;
		ft_memdel((void **)&tmp->title);
		SDL_DestroyWindow(tmp->p);
		next = win->next;
		ft_memdel((void **)&win->content);
		ft_memdel((void **)&win);
	}
	ft_memdel((void **)&g_win_list);
}

inline static void	destroy_fonts(void)
{
	t_flist	*font;
	t_flist	*next;
	t_font	*tmp;

	if (!g_font_list)
		return ;
	font = g_font_list;
	next = font->next;
	while ((font = next) != g_font_list)
	{
		tmp = font->content;
		ft_memdel((void **)&tmp->name);
		TTF_CloseFont(tmp->ttf);
		next = font->next;
		ft_memdel((void **)&font->content);
		ft_memdel((void **)&font);
	}
	ft_memdel((void **)&g_font_list);
}

int					sgl_quit(void)
{
	destroy_wins();
	destroy_fonts();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return (0);
}
