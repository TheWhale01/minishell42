/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:54:40 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/03 17:49:05 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_data *data)
{
	char	*home;
	char	*start;

	start = search_env("HOME", data);
	if (!start)
		return (NULL);
	home = ft_rstrstr(data->pwd, start);
	if (!home)
		home = data->pwd;
	else
		home = ft_strjoin("~", home);
	free(start);
	return (home);
}

char	*ft_prompt(t_data *data)
{
	char	*dir;
	char	*line;
	char	*prompt;

	dir = get_home(data);
	prompt = ft_strjoin_free_s1(search_env("USER", data), "@minishell:");
	if (!ft_strchr(dir, '~'))
		prompt = ft_strjoin_free_s1(prompt, dir);
	else
		prompt = ft_strjoin_free_s1_s2(prompt, dir);
	prompt = ft_strjoin_free_s1(prompt, "$ ");
	line = readline(prompt);
	free(prompt);
	if (!line)
		exit_cmd(EXIT_SUCCESS, data, "", NULL);
	return (line);
}
