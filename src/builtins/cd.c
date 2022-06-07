/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:44:17 by teambersaw        #+#    #+#             */
/*   Updated: 2022/06/07 13:33:01 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *join)
{
	ft_putstr_fd(join, 2);
	ft_putstr_fd(": ", 2);
	perror("\0");
	free(join);
}

int	ft_len_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

int	ft_path_cd(char **arg, char **path, t_data *data)
{
	char		*paths;

	if (ft_len_double(arg) == 1)
	{
		paths = search_env("HOME", data);
		if (paths == NULL)
			return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
	}
	else if (ft_len_double(arg) == 2)
	{
		if (((char *)arg[1])[0] == '\0')
			return (1);
		paths = ft_strdup(arg[1]);
	}
	else
		return (ft_putstr_fd("bash: cd: too many arugments\n", 2), 1);
	*path = paths;
	return (0);
}

int	ft_cd(t_data *data, char **arg)
{
	char	*join;
	char	*str;
	char	*path;

	if (ft_path_cd(arg, &path, data))
		return (1);
	str = ft_strjoin_free_s2("OLDPWD=", data->pwd);
	if (!chdir(path))
	{
		if (!ft_lstexport(data, str))
			ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(str)));
		free(str);
		str = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		if (!ft_lstexport(data, str))
			ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(str)));
	}
	else
	{
		join = ft_strjoin("bash: cd: ", arg[1]);
		ft_perror(join);
	}
	free(path);
	free(str);
	data->pwd = getcwd(NULL, 0);
	return (0);
}
