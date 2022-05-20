/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:46 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/19 20:12:14 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstexport(t_list **lst, char *str)
{
	t_list	*tmp;
	size_t	size;
	size_t	size2;

	if (!lst)
		return (0);
	tmp = *lst;
	while (tmp)
	{
		size = 0;
		size2 = 0;
		while (((char *)tmp->content)[size]
			&& ((char *)tmp->content)[size] != '=')
			size++;
		while (str[size2] && str[size2] != '=')
			size2++;
		if (!ft_strncmp(tmp->content, str, size) && size == size2)
		{
			if (ft_strchr(str, '='))
				tmp->content = str;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_verif(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '=')
		return (1);
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (0);
}

int	ft_export(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	if (!data->envp)
		return (0);
	tmp = data->tokens;
	token = (t_token *)tmp->content;
	if (ft_lstsize(tmp) == 1)
		return (ft_list_sort(data->envp), 0);
	tmp = tmp->next;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (ft_verif(token->str))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(token->str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else if (!ft_lstexport(&data->envp, token->str))
			ft_lstadd_back(&data->envp, ft_lstnew(token->str));
		tmp = tmp->next;
	}
	return (0);
}
