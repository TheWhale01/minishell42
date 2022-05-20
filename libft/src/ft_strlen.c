/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:35:30 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/20 10:03:22 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

size_t	ft_strlclen(const char *str, char *charset)
{
	int		i;
	size_t	len;

	i = -1;
	len = 0;
	while (str && str[++i])
		if (!ft_is_in(str[i], charset))
			len++;
	return (len);
}
