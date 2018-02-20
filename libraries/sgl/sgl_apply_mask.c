/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_apply_mask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:34:38 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/16 16:00:32 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static void	main_loop(t_thread_d *data)
{
	int			i;
	int			j;
	SDL_Surface	*surf;
	t_uint		*pixels;

	surf = (SDL_Surface*)data->data;
	pixels = (t_uint *)surf->pixels;
	i = data->start - 1;
	while (++i < data->end && (j = -1))
		while (++j < surf->h)
			pixels[j * surf->w + i] &= *(t_uint *)surf->userdata;
}

void		sgl_apply_mask(SDL_Surface *surf, t_uint mask)
{
	const int	t_count = 8;
	pthread_t	threads[t_count];
	t_thread_d	data[t_count];
	int			th;
	int			coef;

	surf->userdata = &mask;
	coef = surf->w / t_count;
	th = -1;
	while (++th < t_count)
	{
		data[th] = (t_thread_d){(void *)surf, th * coef, (th + 1) * coef};
		pthread_create(&threads[th], NULL, (void *(*)())main_loop, &data[th]);
	}
	th = -1;
	while (++th < t_count)
		pthread_join(threads[th], NULL);
	surf->userdata = NULL;
}
