/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:25:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/02 11:19:00 by hubretec         ###   ########.fr       */
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

char	**get_pipe_args(t_list *tokens, int pos)
{
	int		i;
	t_list	*tmp;
	t_token	*token;

	i = 0;
	tmp = tokens;
	while (tmp && i < pos)
	{
		token = (t_token *)tmp->content;
		if (token->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (get_args(tmp));
}
