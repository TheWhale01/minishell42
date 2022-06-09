/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:46 by jrossett          #+#    #+#             */
/*   Updated: 2022/06/09 11:05:52 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lst_size(char *strenv, char *str)
{
	size_t	size;
	size_t	size2;

	size = 0;
	size2 = 0;
	while (strenv[size] && strenv[size] != '=')
		size++;
	while (str[size2] && str[size2] != '=')
		size2++;
	if (size == size2)
		return (size);
	return (0);
}

int	ft_lstexport(t_data *data, char *str)
{
	t_list	*tmp;
	size_t	size;

	if (!data->envp)
		return (0);
	tmp = data->envp;
	while (tmp)
	{
		size = lst_size(tmp->content, str);
		if (size)
		{	
			if (!ft_strncmp(tmp->content, str, size))
			{
				if (ft_strchr(str, '='))
				{
					free(tmp->content);
					tmp->content = ft_strdup(str);
				}
				return (1);
			}
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
		else if (!ft_lstexport(data, arg[i]))
			ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(arg[i])));
		if (data->path)
			free_tab(data->path);
		data->path = get_path_env(search_env("PATH", data));
		i++;
	}
	return (0);
}
