/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:30 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/16 15:05:50 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && (s1[i] == s2[i]))
		{
			i++;
		}
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
		return (2);
}
