/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:57 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 19:58:28 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	x = c;
	i = ft_strlen(s);
	if (x == 0)
		return ((char *)&s[i]);
	while (--i >= 0)
		if (s[i] == x)
			return ((char *)&s[i]);
	return (0);
}
