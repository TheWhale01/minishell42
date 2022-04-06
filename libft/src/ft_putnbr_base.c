/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:13:24 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/06 21:43:37 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_base(int nb, char *base, int *len)
{
	int				base_len;
	unsigned int	nbr;

	base_len = ft_strlen(base);
	if (nb < 0)
	{
		nbr = nb * -1;
		*len += write(1, "-", 1);
	}
	else
		nbr = nb;
	if (nbr / base_len)
		ft_putnbr_base(nbr / base_len, base, len);
	*len += write(1, &base[nbr % base_len], 1);
}

void	ft_putnbr_base_u(unsigned int nb, char *base, int *len)
{
	int		base_len;

	base_len = ft_strlen(base);
	if (nb / base_len)
		ft_putnbr_base_u(nb / base_len, base, len);
	*len += write(1, &base[nb % base_len], 1);
}
