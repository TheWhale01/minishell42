/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:54:50 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/30 10:05:57 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_args(t_list *tokens)
{
	int		nb_tokens;
	t_list	*tmp;
	t_token	*token;

	nb_tokens = 0;
	tmp = tokens;
	token = (t_token *)tmp->content;
	while (tmp && (token->token == CMD
			|| token->token == VAR || token->token == WORD))
	{
		nb_tokens++;
		tmp = tmp->next;
		if (tmp)
			token = (t_token *)tmp->content;
	}
	return (nb_tokens);
}

char	**get_args(t_list *tokens)
{
	int		i;
	char	**args;
	t_list	*tmp;
	t_token	*token;

	args = malloc(sizeof(char *) * (get_nb_args(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = tokens;
	token = (t_token *)tmp->content;
	while (tmp && (token->token == CMD
			|| token->token == VAR || token->token == WORD))
	{
		args[i++] = token->str;
		tmp = tmp->next;
		if (tmp)
			token = (t_token *)tmp->content;
	}
	args[i] = NULL;
	return (args);
}
