/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:25:53 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 18:42:22 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

static char	hex_digit(int v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	return ('a' + v - 10);
}

void	print_addr(void *p0, int *len)
{
	int			i;
	uintptr_t	p;

	if (!p0)
	{
		*len += ft_putstr("0x0");
		return ;
	}
	p = (uintptr_t)p0;
	*len += ft_putstr("0x");
	i = (sizeof(p) << 3) - 4;
	while (hex_digit((p >> i) & 0xf) == '0' && i >= 0)
		i -= 4;
	while (i >= 0)
	{
		*len += ft_putchar(hex_digit((p >> i) & 0xf));
		i -= 4;
	}
}
