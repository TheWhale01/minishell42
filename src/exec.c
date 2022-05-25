/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/25 16:45:48 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_data *data)
{
	t_token	*token;

	token = (t_token *)data->tokens->content;
	if (!ft_strcmp(token->str, "cd"))
		ft_cd(data);
	else if (!ft_strcmp(token->str, "env"))
		ft_env(data);
	else if (!ft_strcmp(token->str, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(token->str, "exit"))
		exit_cmd(EXIT_SUCCESS, data, NULL);
	else if (!ft_strcmp(token->str, "unset"))
		ft_unset(data);
	else if (!ft_strcmp(token->str, "export"))
		ft_export(data);
}

void	exec_cmd(t_data *data)
{
	make_redirs(data);
	if (is_builtin(((t_token *)data->tokens->content)->str))
		exec_builtin(data);
	restore_redirs(data);
}
