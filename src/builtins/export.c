/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:46 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/31 13:51:06 by jrossett         ###   ########.fr       */
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
			{
				free(tmp->content);
				tmp->content = ft_strdup(str);
			}
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

int	ft_export(t_data *data, char **arg)
{
	int	i;

	if (!data->envp)
		return (0);
	if (ft_len_double(arg) == 1)
		return (ft_list_sort(data->envp), 0);
	i = 1;
	while (arg[i])
	{
		if (ft_verif(arg[i]))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else if (!ft_lstexport(&data->envp, arg[i]))
			ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(arg[i])));
		free_tab(data->path);
		data->path = get_path_env(list_to_tab(data->envp));
		i++;
	}
	return (0);
}
