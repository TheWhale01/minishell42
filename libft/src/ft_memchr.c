/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:10:52 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 19:55:55 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	to_find;
	unsigned char	*tab;

	i = 0;
	tab = (unsigned char *)s;
	to_find = (unsigned char)c;
	while (i < n)
		if (tab[i++] == to_find)
			return (&tab[i - 1]);
	return (0);
}
