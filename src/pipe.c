/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/01 21:34:15 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipe(t_data *data, int index)
{
	if (!index)
		connect_first(data);
	else if (index == data->childs->nb_pipes)
		connect_last(data);
	else
	{
		close(data->childs[index].fd[0]);
		close(data->childs[index + 1].fd[1]);
		data->fd_in = dup(STDIN);
		data->fd_out = dup(STDOUT);
		dup2(data->childs[index].fd[1], STDIN);
		dup2(data->childs[index + 1].fd[0], STDOUT);
		close(data->childs[index + 1].fd[0]);
		close(data->childs[index].fd[1]);
	}
}

void	exec_pipeline(t_data *data, char **args)
{
	int	i;

	i = 0;
	make_redirs(data);
	while (!is_redir(args[i]))
		i += 2;
	if (is_builtin(args[0]))
		exec_builtin(args, data);
	restore_redirs(data);
}

void	launch_pipe(t_data *data, int pipe_index)
{
	char	**args;

	args = get_pipe_args(data->tokens, pipe_index);
	exec_pipeline(data, args);
	free(args);
	exit_cmd(EXIT_SUCCESS, data, NULL);
}

void	create_childs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->childs->nb_pipes + 1)
	{
		if (!i || data->childs[i - 1].pid)
			data->childs[i].pid = fork();
		if (!data->childs[i].pid)
		{
			connect_pipe(data, i);
			launch_pipe(data, i);
		}
		else
			waitpid(data->childs[i].pid, NULL, 0);
	}
}

void	init_pipeline(t_data *data)
{
	int	i;
	int	nb_pipes;

	nb_pipes = get_nb_pipes(data->tokens);
	data->childs = malloc(sizeof(t_subp) * (nb_pipes + 1));
	if (!data->childs)
		return ;
	i = -1;
	while (data->childs && ++i < nb_pipes)
	{
		data->childs[i].pid = 1;
		data->childs[i].nb_pipes = nb_pipes;
		pipe(data->childs[i].fd);
		close(data->childs[i].fd[0]);
		close(data->childs[i].fd[1]);
	}
	data->childs[i].fd[0] = -1;
	data->childs[i].fd[1] = -1;
	create_childs(data);
}
