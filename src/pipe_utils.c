/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:25:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/01 21:33:31 by hubretec         ###   ########.fr       */
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

char	**get_pipe_args(t_list *tokens, int pos)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	while (tmp && pos)
	{
		token = (t_token *)tmp->content;
		if (token->token == PIPE)
			pos--;
		tmp = tmp->next;
	}
	return (get_args(tmp));
}
