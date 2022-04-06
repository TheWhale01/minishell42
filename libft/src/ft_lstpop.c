/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:48:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/28 18:25:38 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*pop_first(t_list **lst)
{
	t_list	*pop;

	pop = *lst;
	(*lst) = (*lst)->next;
	pop->next = NULL;
	return (pop);
}

static t_list	*pop_last(t_list **lst)
{
	t_list	*tmp;
	t_list	*pop;

	tmp = *lst;
	pop = ft_lstlast(*lst);
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next = NULL;
	return (pop);
}

t_list	*ft_lstpop(t_list **lst, t_list *node)
{
	t_list	*tmp;
	t_list	*pop;

	if (*(int *)(*lst)->content == *(int *)node->content)
		return (pop_first(lst));
	if (*(int *)ft_lstlast(*lst)->content == *(int *)node->content)
		return (pop_last(lst));
	tmp = *lst;
	while (tmp->next && *(int *)tmp->next->content != *(int *)node->content)
		tmp = tmp->next;
	pop = tmp->next;
	tmp->next = tmp->next->next;
	pop->next = NULL;
	return (pop);
}
