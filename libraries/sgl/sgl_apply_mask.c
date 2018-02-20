/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_apply_mask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:34:38 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void		sgl_apply_mask(SDL_Surface *surf, t_uint mask)
{
	int		x;
	int		y;
	int		w;
	t_uint	*row;

	w = surf->w;
	y = -1;
	while (++y < surf->h && (x = -1))
	{
		row = (t_uint *)((char *)surf->pixels + y * surf->pitch);
		while (++x < w)
			row[x] &= mask;
	}
}
