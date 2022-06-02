/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/02 15:25:09 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipeline(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (is_builtin(args[i]))
		exec_builtin(&args[i], data);
	else
		exec_cmd(args, data);
}

void	launch_pipe(t_data *data, int pipe_index)
{
	char	**args;

	args = get_args(skip_pipes(data->tokens, pipe_index));
	exec_pipeline(data, args);
	if (!pipe_index)
		exit_cmd(EXIT_SUCCESS, data, NULL);
}

void	init_pipeline(t_data *data)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1)
		pid2 = fork();
	if (!pid1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		launch_pipe(data, 0);
	}
	if (!pid2)
	{
		waitpid(pid1, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		launch_pipe(data, 1);
	}
}
