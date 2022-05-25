/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:44:17 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/25 17:54:50 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_path_cd(t_list *tmp, char **path, t_data *data)
{
	char		*paths;

	if (ft_lstsize(tmp) == 1)
	{
		paths = search_env("HOME", data);
		if (paths == NULL)
			return (1);
	}
	else if (ft_lstsize(tmp) == 2)
		paths = ((t_token *)tmp->next->content)->str;
	else
		return (printf("cd: too many arugment\n"), 1);
	*path = paths;
	return (0);
}

int	ft_cd(t_data *data)
{
	char	*str;
	char	*path;
	t_list	*tmp;

	tmp = data->tokens;
	if (ft_path_cd(tmp, &path, data))
		return (1);
	str = ft_strjoin_free_s2("OLDPWD=", getcwd(NULL, 0));
	if (!ft_lstexport(&data->envp, str))
		ft_lstadd_back(&data->envp, ft_lstnew(str));
	free(str);
	if (!chdir(path))
	{
		str = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		if (!ft_lstexport(&data->envp, str))
			ft_lstadd_back(&data->envp, ft_lstnew(str));
		free(str);
	}
	else
		perror("cd");
	return (0);
}
