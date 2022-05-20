/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:44:17 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/20 23:14:16 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *data)
{
	char	*str;
	char	*path;
	DIR		*dir;
	t_list	*tmp;

	tmp = data->tokens;
	if (ft_lstsize(tmp) == 1)
		path = search_env("HOME", data->envp);
	else if (ft_lstsize(tmp) == 2)
		path = ((t_token *)tmp->next->content)->str;
	else
		return (printf("too many arugment\n"), 0);
	dir = opendir(path);
	if (!dir)
		return(printf("PAS UN DOSSIER\n"), 0);
	str = ft_strjoin_free_s2("OLDPWD=", getcwd(NULL, 0));
	if (!ft_lstexport(&data->envp, str))
		ft_lstadd_back(&data->envp, ft_lstnew(str));
	//free(str);
	if (!chdir(path))
	{
		str = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		if (!ft_lstexport(&data->envp, str))
			ft_lstadd_back(&data->envp, ft_lstnew(str));
	//	free(str);
	}
	else 
		printf("oupsi\n");
	closedir(dir);
	return (0);
}