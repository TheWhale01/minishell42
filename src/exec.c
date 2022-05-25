/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/25 18:31:15 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_list	*cmd, t_data *data)
{
	t_token	*token;

	if (!cmd)
		return ;
	token = (t_token *)cmd->content;
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
	t_list	*start;
	t_token	*start_token;

	start = data->tokens;
	start_token = (t_token *)start->content;
	make_redirs(data);
	while (start_token->token == REDIR_IN || start_token->token == REDIR_OUT
		|| start_token->token == D_REDIR_IN
		|| start_token->token == D_REDIR_OUT)
	{
		start = skip_redirs(start);
		start_token = (t_token *)start->content;
	}
	if (is_builtin(((t_token *)start->content)->str))
		exec_builtin(start, data);
	restore_redirs(data);
}
