/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:42:13 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/07 10:02:27 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	if (!tmp)
		return ;
	if (((t_token *)tmp->content)->token == PIPE)
		ft_exit(data, "minishell: syntax error '|'", EXIT_FAILURE, NULL);
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == PIPE
			&& (!tmp->next || ((t_token *)tmp->next->content)->token == PIPE))
			ft_exit(data, "minishell: syntax error '|'", EXIT_FAILURE, NULL);
		if (is_redir(token->str)
			&& (!tmp->next || (is_redir(((t_token *)tmp->next->content)->str))))
			ft_exit(data, "minishell: syntax error 'redirection'",
				EXIT_FAILURE, NULL);
		tmp = tmp->next;
	}
}