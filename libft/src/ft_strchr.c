/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:09 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 19:57:45 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	i = -1;
	x = c;
	while (s && s[++i])
		if (s[i] == x)
			return ((char *)&s[i]);
	if (s && s[i] == x)
		return ((char *)&s[i]);
	return (0);
}
