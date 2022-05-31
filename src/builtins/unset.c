/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 04:58:04 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/31 13:59:26 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif_unset(char	*str)
{
	int	i;

	i = 0;
	if (str[i] && ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (0);
}

int	ft_lstunset(t_list **lst, char *str)
{
	t_list	*del;
	t_list	*tmp;
	size_t	size;

	tmp = *lst;
	size = ft_strlen(str);
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, str, size) == 0)
		{
			del = ft_lstpop(lst, tmp);
			ft_lstdelone(del, free);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset(t_data *data, char **arg)
{
	int	i;

	if (ft_len_double(arg) == 1)
		return (0);
	i = 1;
	while (arg[i])
	{
		if (ft_verif_unset(arg[i]))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			ft_lstunset(&data->envp, arg[i]);
		i++;
		free_tab(data->path);
		data->path = get_path_env(list_to_tab(data->envp));
	}
	return (0);
}
