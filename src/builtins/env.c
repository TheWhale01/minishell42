/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:06:23 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/20 23:25:49 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_list(char **envp)
{
	char	*str;
	t_list	*list;
	t_list	*tmp;
	int		i;

	i = 1;
	if (!*envp || !(**envp))
	{
		list = ft_lstnew(NULL);
		return (list);
	}
	str = ft_strdup(envp[0]);
	list = ft_lstnew(str);
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		tmp = ft_lstnew(str);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	return (list);
}

void	ft_env(t_data *data)
{
	t_list	*tmp;

	tmp = data->envp;
	if (tmp->content)
	{
		while (tmp)
		{
			if (ft_strchr((char *)tmp->content, '='))
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
