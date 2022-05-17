/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/17 03:11:42 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

char	*search_env(char *str, t_list *envp)
{
	int		len;
	t_list	*tmp;

	if (!varlen(str))
		return ("$");
	if (*str == '$')
		str++;
	if (*str == '?')
		return ("***value of last cmd***");
	else if (ft_isdigit(*str))
		return (NULL);
	tmp = envp;
	while (tmp)
	{
		len = 0;
		while (((char *)tmp->content)[len]
			&& ((char *)tmp->content)[len] != '=')
			len++;
		if (!ft_strncmp(str, (char *)tmp->content, len))
			return (ft_strchr(tmp->content, '=') + 1);
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
