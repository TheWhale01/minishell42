/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:09 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/18 14:50:33 by teambersaw       ###   ########.fr       */
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
