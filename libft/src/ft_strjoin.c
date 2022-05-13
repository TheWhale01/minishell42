/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:14:55 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/13 11:17:03 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	int		s2len;
	char	*str;

	s2len = ft_strlen(s2);
	s1len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[i - s1len])
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	if (s1)
		free((char *)s1);
	return (str);
}

char	*ft_strjoin_free_s2(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	char	*str;

	s1len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1len + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - s1len])
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	if (s2)
		free((char *)s2);
	return (str);
}

char	*ft_strjoin_free_s1_s2(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	char	*str;

	s1len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1len + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - s1len])
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	if (s1)
		free((char *)s1);
	if (s2)
		free((char *)s2);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1len;
	char	*str;

	s1len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1len + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - s1len])
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	return (str);
}
