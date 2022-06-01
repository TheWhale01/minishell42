/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/01 21:25:27 by hubretec         ###   ########.fr       */
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
		path_cmd = ft_strjoin_free_s1(tmp, cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		free(path_cmd);
		env++;
	}
	return (NULL);
}

void	exec_builtin(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "env"))
		ft_env(data);
	else if (!ft_strcmp(args[0], "exit"))
	{
		free(args);
		exit_cmd(EXIT_SUCCESS, data, "exit");
	}
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(data, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(data, args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(data, args);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(data, args);
	free(args);
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
			ft_putstr_fd(args[0], STDERR);
			ft_putstr_fd(": command not found\n", STDERR);
		}
		else if (execve(path, args, env) == -1)
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
	if (search_token(data->tokens, PIPE))
		init_pipeline(data);
	else if (is_builtin(((t_token *)start->content)->str))
		exec_builtin(NULL, data);
	else
		exec_cmd(start, data);
	restore_redirs(data);
}
