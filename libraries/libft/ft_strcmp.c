/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:04:56 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:57:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-*s2);
	else if (!s2)
		return (*s1);
	while (*s1 || *s2)
		if (*s1++ != *s2++)
			return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
	return (0);
}
