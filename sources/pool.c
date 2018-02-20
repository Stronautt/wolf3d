/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:26:56 by stronautt         #+#    #+#             */
/*   Updated: 2026/11/02 20:26:56 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_pool	g_pool;

static int		pool_worker(void *arg)
{
	(void)arg;
	while (1)
	{
		SDL_WaitSemaphore(g_pool.go);
		if (g_pool.quit)
			return (0);
		ft_draw_heart(g_pool.gd, &g_pool.next);
		SDL_SignalSemaphore(g_pool.done);
	}
}

static int		pool_size(void)
{
	const char	*env;
	int			n;

	n = SDL_GetNumLogicalCPUCores();
	(env = SDL_getenv("WOLF_THREADS")) ? n = ft_atoi(env) : 0;
	n > RENDER_MAX_THREADS ? n = RENDER_MAX_THREADS : 0;
	return (n < 1 ? 1 : n);
}

static void		pool_init(void)
{
	int		i;

	g_pool.n = pool_size();
	g_pool.n > 1 ? g_pool.go = SDL_CreateSemaphore(0) : 0;
	g_pool.n > 1 ? g_pool.done = SDL_CreateSemaphore(0) : 0;
	i = 0;
	while (g_pool.go && g_pool.done && i < g_pool.n - 1
		&& (g_pool.th[i] = SDL_CreateThread(pool_worker, "render", NULL)))
		i++;
	g_pool.n = i + 1;
}

void			render_frame(t_game *gd)
{
	int		i;

	if (!g_pool.n)
		pool_init();
	g_pool.gd = gd;
	SDL_SetAtomicInt(&g_pool.next, 0);
	i = -1;
	while (++i < g_pool.n - 1)
		SDL_SignalSemaphore(g_pool.go);
	ft_draw_heart(gd, &g_pool.next);
	i = -1;
	while (++i < g_pool.n - 1)
		SDL_WaitSemaphore(g_pool.done);
}

void			render_quit(void)
{
	int		i;

	g_pool.quit = 1;
	i = -1;
	while (++i < g_pool.n - 1)
		SDL_SignalSemaphore(g_pool.go);
	i = -1;
	while (++i < g_pool.n - 1)
		SDL_WaitThread(g_pool.th[i], NULL);
	SDL_DestroySemaphore(g_pool.go);
	SDL_DestroySemaphore(g_pool.done);
}
