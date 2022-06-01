/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/01 16:42:07 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_pipes(t_list	*tokens)
{
	int		pipes;
	t_list	*tmp;
	t_token	*token;

	pipes = 0;
	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == PIPE)
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
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
}

void	connect_first(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->childs->nb_pipes)
	{
		close(data->childs[i].fd[0]);
		close(data->childs[i].fd[1]);
	}
	data->fd_out = dup(STDOUT);
	close(data->childs[0].fd[1]);
	dup2(data->childs[0].fd[0], STDOUT);
	close(data->childs[0].fd[0]);
}

void	connect_last(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->childs->nb_pipes - 1)
	{
		close(data->childs[i].fd[0]);
		close(data->childs[i].fd[1]);
	}
	data->fd_in = dup(STDIN);
	close(data->childs[i].fd[0]);
	dup2(data->childs[i].fd[1], STDIN);
	close(data->childs[i].fd[1]);
}

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

void	launch_pipe(t_data *data, int pipe_index)
{
	(void)data;
	(void)pipe_index;
	exit_cmd(EXIT_SUCCESS, data, "exit fork");
}

void	create_childs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->childs->nb_pipes + 1)
	{
		if (!i || data->childs[i - 1].pid)
		{
			if (!i)
				data->childs[i].pid = fork();
			else
				data->childs[i].pid = fork();
		}
		if (!data->childs[i].pid)
		{
			printf("FORK\n");
			connect_pipe(data, i);
			launch_pipe(data, i + 1);
		}
		else
			waitpid(data->childs[i].pid, NULL, 0);
	}
}

void	exec_pipeline(t_data *data)
{
	init_pipeline(data);
	create_childs(data);
	return ;
}
