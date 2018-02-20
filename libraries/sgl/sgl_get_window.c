/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_get_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:56:38 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/09 19:00:04 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_sgl_window	*sgl_get_window(char *title)
{
	t_wlist			*win;
	t_sgl_window	*tmp;

	if (!g_win_list)
		return (NULL);
	win = g_win_list;
	while ((win = win->next) != g_win_list)
	{
		tmp = win->content;
		if (!ft_strcmp(tmp->title, title))
			return (tmp);
	}
	return (NULL);
}
