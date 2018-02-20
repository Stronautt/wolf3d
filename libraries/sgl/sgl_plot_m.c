/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_plot_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 20:14:35 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/16 20:16:27 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_plot_m(t_point p, t_uint color, SDL_Surface *surface, t_uint mask)
{
	mask ? color &= mask : 0;
	sgl_plot(p, color, surface);
}
