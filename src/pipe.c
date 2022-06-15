/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/14 15:39:43 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipes(t_data *data, int child_index)
{
	if (!child_index)
	{
		close(data->pipeline.pipes[0][0]);
		dup2(data->pipeline.pipes[0][1], STDOUT_FILENO);
		close(data->pipeline.pipes[0][1]);
	}
	else if (child_index == data->pipeline.nb_pipes)
	{
		close(data->pipeline.pipes[child_index - 1][1]);
		dup2(data->pipeline.pipes[child_index - 1][0], STDIN_FILENO);
		close(data->pipeline.pipes[child_index - 1][0]);
	}
	else
	{
		dup2(data->pipeline.pipes[child_index - 1][0], STDIN_FILENO);
		dup2(data->pipeline.pipes[child_index][1], STDOUT_FILENO);
	}
}

void	init_pipes(t_data *data, t_pipeline *pipeline)
{
	int	i;

	i = -1;
	pipeline->pipes = malloc(sizeof(int *) * pipeline->nb_pipes);
	if (!pipeline->pipes)
		exit_cmd(EXIT_FAILURE, data, "Memory allocation error.", NULL);
	while (++i < pipeline->nb_pipes)
	{
		pipeline->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipeline->pipes[i])
			exit_cmd(EXIT_FAILURE, data, "Memory allocation error", NULL);
		pipe(data->pipeline.pipes[i]);
	}
}

void	launch_pipe(t_data *data, int child_index)
{
	char	**args;
	t_list	*start;

	connect_pipes(data, child_index);
	start = skip_pipes(data->tokens, child_index);
	make_redirs(data, start);
	args = get_args(skip_redirs(start));
	if (is_builtin(*args))
		exec_builtin(args, data);
	else
		exec_cmd(args, data);
	free_pipes(data);
	free(data->pipeline.children);
	restore_redirs(data);
	exit_cmd(EXIT_SUCCESS, data, NULL, NULL);
	exit(EXIT_SUCCESS);
}

void	init_pipeline(t_data *data)
{
	int	i;

	i = -1;
	data->pipeline.nb_pipes = get_nb_pipes(data->tokens);
	data->pipeline.nb_children = data->pipeline.nb_pipes + 1;
	init_pipes(data, &data->pipeline);
	data->pipeline.children = malloc(sizeof(pid_t)
			* data->pipeline.nb_children);
	if (!data->pipeline.children)
		exit_cmd(EXIT_FAILURE, data, "Memory allocation error.", NULL);
	while (++i < data->pipeline.nb_children)
	{
		data->pipeline.children[i] = fork();
		if (!data->pipeline.children[i])
			launch_pipe(data, i);
		else
			waitpid(data->pipeline.children[i], NULL, 0);
	}
	close_pipes(data);
	free_pipes(data);
	free(data->pipeline.children);
}

// void	init_pipeline(t_data *data)
// {
// 	int		fd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	pipe(fd);
// 	pid1 = fork();
// 	if (pid1)
// 		pid2 = fork();
// 	if (!pid1)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		launch_pipe(data, 0);
// 	}
// 	else if (!pid2)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		launch_pipe(data, 1);
// 	}
// 	else
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		waitpid(pid1, NULL, 0);
// 		waitpid(pid2, NULL, 0);
// 	}
// }
