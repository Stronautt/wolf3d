/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_fix_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:42:46 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/15 14:44:18 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_fix_point(t_point *p, SDL_Surface *surface)
{
	p->x < 0 ? p->x = 0 : 0;
	p->x >= surface->w ? p->x = surface->w - 1 : 0;
	p->y < 0 ? p->y = 0 : 0;
	p->y >= surface->h ? p->y = surface->h - 1 : 0;
}
