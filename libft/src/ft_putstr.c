/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:12:41 by hubretec          #+#    #+#             */
/*   Updated: 2021/12/19 18:41:28 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char const *s, int fd)
{
	int	len;

	len = 0;
	while (*s)
		len += write(fd, s++, 1);
	return (len);
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (*str)
		len += write(1, str++, 1);
	return (len);
}
