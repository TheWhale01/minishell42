/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/02 11:21:11 by hubretec         ###   ########.fr       */
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

	args = get_pipe_args(data->tokens, pipe_index);
	exec_pipeline(data, args);
	free(args);
	exit(EXIT_SUCCESS);
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
			launch_pipe(data, i);
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
