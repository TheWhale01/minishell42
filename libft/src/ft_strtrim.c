/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:27:29 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 19:58:32 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in(char const c, char const *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

static void	blank_len(char const *s1, char const *set, int *start, int *end)
{
	*start = 0;
	while (s1[*start] && is_in(s1[*start], set))
		*start = *start + 1;
	*end = ft_strlen(s1) - 1;
	while (*end >= 0 && is_in(s1[*end], set))
		*end = *end - 1;
	if (*start > *end)
	{
		*start = 0;
		*end = -1;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		end;
	int		len;
	int		start;
	char	*str;

	blank_len(s1, set, &start, &end);
	len = (end - start) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
