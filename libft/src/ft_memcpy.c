/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:11:38 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 19:56:47 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*tab_dest;
	const char	*tab_src;

	tab_src = (char *)src;
	tab_dest = (char *)dest;
	while (n--)
		*(tab_dest++) = *(tab_src++);
	return (dest);
}
