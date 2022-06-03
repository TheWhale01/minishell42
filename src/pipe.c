/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/03 17:48:46 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipeline(t_data *data, char **args)
{
	if (is_builtin(*args))
		exec_builtin(args, data);
	else
		exec_cmd(args, data);
}

void	launch_pipe(t_data *data, int pipe_index)
{
	char	**args;
	t_list	*start;

	start = skip_pipes(data->tokens, pipe_index);
	make_redirs(data, start);
	args = get_args(skip_redirs(start));
	exec_pipeline(data, args);
	restore_redirs(data);
	exit_cmd(data->rtn_val, data, NULL, NULL);
}

void	init_pipeline(t_data *data)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (!pid1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		launch_pipe(data, 0);
	}
	pid2 = fork();
	if (!pid2)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		launch_pipe(data, 1);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}
