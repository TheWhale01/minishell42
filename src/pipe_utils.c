/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:25:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/14 14:21:55 by hubretec         ###   ########.fr       */
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

t_list	*skip_pipes(t_list *tokens, int pos)
{
	t_list	*tmp;

	tmp = tokens;
	if (!pos)
		return (tmp);
	while (tmp && pos)
	{
		if (((t_token *)tmp->content)->token == PIPE)
			pos--;
		tmp = tmp->next;
	}
	return (tmp);
}

void	free_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->pipeline.nb_pipes)
	{
		close(data->pipeline.pipes[i][0]);
		close(data->pipeline.pipes[i][1]);
		free(data->pipeline.pipes[i]);
	}
	free(data->pipeline.pipes);
}