/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:03:43 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/13 15:16:08 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	print_msg(const char *msg, const char *add, int err, t_uchar stop)
{
	if (stop)
	{
		if (err && add)
			ft_printf("{red}%s: {yellow}%s{nc} - {red}%s{nc}\n",
			msg, add, strerror(errno));
		else if (msg && add)
			ft_printf("{red}Error: {yellow}%s : %s{nc}\n", msg, add);
		else
			err ? ft_printf("%s: {red}%s{nc}\n", msg, strerror(err))
				: ft_printf("{red}Error: {yellow}%s{nc}\n", msg);
	}
	else
	{
		if (err && add)
			ft_printf("{yellow}%s: {cyan}%s{nc} - {red}%s{nc}\n",
			msg, add, strerror(errno));
		else if (msg && add)
			ft_printf("{yellow}Warning: {cyan}%s : %s{nc}\n", msg, add);
		else
			err ? ft_printf("%s: {red}%s{nc}\n", msg, strerror(err))
				: ft_printf("{yellow}Warning: {cyan}%s{nc}\n", msg);
	}
}

void		ft_err_handler(const char *msg, const char *add, int err,
							t_uchar stop)
{
	msg ? print_msg(msg, add, err, stop) : 0;
	if (!stop)
		return ;
	msg ? ERR_BOX(PROGRAM_NAME, msg) : 0;
	render_quit();
	sgl_quit();
	exit(err ? err : -1);
}
