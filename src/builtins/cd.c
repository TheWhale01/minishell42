/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:44:17 by teambersaw        #+#    #+#             */
/*   Updated: 2022/06/01 11:10:05 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (1);
	}
	else if (ft_len_double(arg) == 2)
		paths = ft_strdup(arg[1]);
	else
		return (printf("cd: too many arugment\n"), 1);
	*path = paths;
	return (0);
}

int	ft_cd(t_data *data, char **arg)
{
	char	*str;
	char	*path;

	if (ft_path_cd(arg, &path, data))
		return (1);
	str = ft_strjoin_free_s2("OLDPWD=", data->pwd);
	if (!chdir(path))
	{
		if (!ft_lstexport(&data->envp, str))
			ft_lstadd_back(&data->envp, ft_lstnew(str));
		free(str);
		str = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		if (!ft_lstexport(&data->envp, str))
			ft_lstadd_back(&data->envp, ft_lstnew(str));
	}
	else
		perror("cd");
	free(path);
	data->pwd = getcwd(NULL, 0);
	free(str);
	return (0);
}
