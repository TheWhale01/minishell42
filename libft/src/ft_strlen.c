/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:35:30 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/01 14:25:09 by jrossett         ###   ########.fr       */
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
	size_t		i;

	i = 0;
	while (str && str[i] && !ft_is_in(str[i], charset))
		i++;
	return (i);
}
