/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 18:13:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/04 13:13:41 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*p_d;

	p_d = s1;
	while (*p_d)
		p_d++;
	while (*s2 && n--)
		*p_d++ = *s2++;
	*p_d = 0;
	return (s1);
}