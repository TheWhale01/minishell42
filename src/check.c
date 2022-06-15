/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:42:13 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/15 17:01:58 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	if (tmp && ((t_token *)tmp->content)->token == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near '|'\n", STDERR_FILENO);
		return (0);
	}
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if ((token->token == PIPE
				&& (!tmp->next || ((t_token *)tmp->next->content)->token
					== PIPE)) || (is_redir(token->str)
				&& (!tmp->next || (is_redir(((t_token *)
								tmp->next->content)->str)))))
		{
			ft_putstr_fd("minishell: syntax error near token\n", STDERR_FILENO);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
