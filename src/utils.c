/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/12 15:04:16 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *skip_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

t_list	*search_env(char *str, t_list *envp)
{
	int		len;
	t_list	*tmp;

	tmp = envp;
	while (tmp)
	{
		len = 0;
		while (((char *)tmp->content)[len] && ((char *)tmp->content)[len] != '=')
			len++;
		if (!ft_strncmp(str, (char *)tmp->content, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_path_env(char **env)
{
	int		i;
	char	**path;

	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
		{
			i = -1;
			path = ft_split(&((*env)[5]), ':');
			while (path[++i])
				path[i] = ft_strjoin_free_s1(path[i], "/");
			return (path);
		}
		env++;
	}
	return (NULL);
}
