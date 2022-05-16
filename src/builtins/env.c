/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:06:23 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/16 11:05:35 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_list(char **envp)
{
	t_list	*list;
	t_list	*tmp;
	int		i;

	i = 1;
	if (!*envp || !(**envp))
	{
		list = ft_lstnew(NULL);
		return (list);
	}
	list = ft_lstnew(envp[0]);
	while (envp[i])
	{
		tmp = ft_lstnew(envp[i]);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	return (list);
}

void	ft_env(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if ((*list)->content)
	{
		while (tmp)
		{
			printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp;
	t_list	*v;

	tmp = list;
	while (tmp)
	{
		v = tmp->next;
		free(tmp);
		tmp = v;
	}
	list = NULL;
}

