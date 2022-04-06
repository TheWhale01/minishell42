/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find_at_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:15:37 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/28 18:34:37 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_find_at_index(t_list *lst, int index)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = lst;
	while (tmp && ++i < index)
		tmp = tmp->next;
	return (tmp);
}
