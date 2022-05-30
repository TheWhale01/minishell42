/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/30 17:04:26 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_cmd(char *cmd, char **env)
{
	char	*tmp;
	char	*path_cmd;

	if (!access(cmd, F_OK))
		return (cmd);
	while (env && *env)
	{
		tmp = ft_strdup(*env);
		path_cmd = ft_strjoin(tmp, cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		free(path_cmd);
		env++;
	}
	return (NULL);
}

void	exec_builtin(t_list	*cmd, t_data *data)
{
	t_token	*token;

	token = (t_token *)cmd->content;
	if (!ft_strcmp(token->str, "env"))
		ft_env(data);
	else if (!ft_strcmp(token->str, "exit"))
		exit_cmd(EXIT_SUCCESS, data, NULL);
	else if (!ft_strcmp(token->str, "cd"))
		ft_cd(data);
	else if (!ft_strcmp(token->str, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(token->str, "unset"))
		ft_unset(data);
	else if (!ft_strcmp(token->str, "export"))
		ft_export(data);
	else if (!ft_strcmp(token->str, "echo"))
		ft_echo(data);
}

void	exec_cmd(t_list	*tokens, t_data *data)
{
	int		pid;
	char	*path;
	char	**env;
	char	**args;

	pid = fork();
	if (!pid)
	{
		env = list_to_tab(data->envp);
		path = get_path_cmd(((t_token *)tokens->content)->str, data->path);
		args = get_args(tokens);
		if (!path)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		if (execve(path, args, env) == -1)
			perror(args[0]);
		free(env);
		free(args);
	}
	waitpid(pid, NULL, 0);
}

void	exec(t_data *data)
{
	t_list	*start;
	t_token	*start_token;

	start = data->tokens;
	if (!start)
		return ;
	start_token = (t_token *)start->content;
	make_redirs(data);
	while (start_token->token == REDIR_IN || start_token->token == REDIR_OUT
		|| start_token->token == D_REDIR_IN
		|| start_token->token == D_REDIR_OUT)
	{
		start = skip_redirs(start);
		if (!start)
			return (restore_redirs(data));
		start_token = (t_token *)start->content;
	}
	if (is_builtin(((t_token *)start->content)->str))
		exec_builtin(start, data);
	else
		exec_cmd(start, data);
	restore_redirs(data);
}
