/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:45:41 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 19:56:54 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char	*src_c;
	char	*dst_c;

	src_c = src;
	dst_c = dest;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
		while ((int)--n >= 0)
			*(dst_c + n) = *(src_c + n);
	return (dest);
}
