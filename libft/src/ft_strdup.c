/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:20 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/02 12:11:03 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*string;

	if (!src)
		return (NULL);
	string = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!string)
		return (NULL);
	i = -1;
	while (src[++i] != '\0')
		string[i] = src[i];
	string[i] = '\0';
	return (string);
}

char	*ft_strndup(char *src, size_t n)
{
	char		*string;
	size_t		i;

	string = malloc(sizeof(char) * (n + 1));
	if (!string)
		return (0);
	i = 0;
	while (src[i] && i < n)
	{
		string[i] = src[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
