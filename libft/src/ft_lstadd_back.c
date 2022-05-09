/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:26:49 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/09 15:22:24 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstadd_back(t_list **list, t_list *tmp)
{
	t_list	*end;

	end = *list;
	while (end->next)
		end = end->next;
	end->next = tmp;
}
