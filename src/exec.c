/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/03 11:54:16 by hubretec         ###   ########.fr       */
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

void	exec_cmd(char **args, t_data *data)
{
	char	*path;
	char	**env;

	env = list_to_tab(data->envp);
	path = get_path_cmd(args[0], data->path);
	if (!path)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		free(env);
		exit_cmd(EXIT_FAILURE, data, ": command not found");
	}
	if (path && execve(path, args, env) == -1)
		perror(args[0]);
	free(env);
}

void	exec(t_data *data)
{
	int		pid;
	char	**args;

	if (search_token(data->tokens, PIPE))
	{
		init_pipeline(data);
		return ;
	}
	args = get_args(skip_redirs(data->tokens));
	make_redirs(data, data->tokens);
	if (is_builtin(args[0]))
		exec_builtin(args, data);
	else
	{
		pid = fork();
		if (!pid)
		{
			exec_cmd(args, data);
			exit_cmd(data->rtn_val, data, NULL);
		}
		else
			waitpid(pid, NULL, 0);
		free(args);
	}
	restore_redirs(data);
}
