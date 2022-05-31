/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:43 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/31 11:45:23 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && (size_t)(i + needle_len) <= len)
	{
		if (haystack[i] == *needle
			&& !ft_strncmp(&haystack[i], needle, needle_len))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	i = -1;
	while (haystack[++i])
		if (haystack[i] == *needle
			&& !ft_strncmp(&haystack[i], needle, needle_len))
			return ((char *)&haystack[i]);
	return (NULL);
}

char	*ft_rstrstr(const char *haystack, const char *needle)
{
	int		i;
	int		needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	i = -1;
	while (haystack[++i])
		if (haystack[i] == *needle
			&& !ft_strncmp(&haystack[i], needle, needle_len))
			return ((char *)&haystack[i + needle_len]);
	return (NULL);
}
