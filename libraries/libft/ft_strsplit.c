/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:24:49 by pgritsen          #+#    #+#             */
/*   Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s_count(char *s, char c)
{
	size_t	words;

	if (!s)
		return (0);
	words = 1;
	while (*s)
	{
		if (*s == c && words++)
			while (*s && *s == c)
				s++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

static void		*clean_list(char **list)
{
	char	**tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (*tmp)
		free(*tmp++);
	free(list);
	return (NULL);
}

static int		add_vord(char **list, size_t *it, char **p_s, char c)
{
	size_t	w_l;

	w_l = ft_strclen(*p_s, c);
	if (!(list[(*it)++] = ft_strsub(*p_s, 0, w_l)))
		return (0);
	*p_s += w_l;
	while (**p_s && **p_s == c)
		(*p_s)++;
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**list;
	char	*p_s;
	char	*cur;
	long	s_c;
	size_t	it;

	if (!s)
		return (NULL);
	p_s = ft_strntrim(s, c);
	s_c = (long)s_count(p_s, c);
	if (!(list = (char **)malloc(sizeof(char *) * (s_c + 1))))
		return (NULL);
	!*p_s ? *list = (char *)(size_t)--s_c : 0;
	it = 0;
	cur = p_s;
	while (s_c-- > 0)
		if (!add_vord(list, &it, &cur, c))
			return (clean_list(list));
	free(p_s);
	list[it] = 0;
	return (list);
}
