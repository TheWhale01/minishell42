/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:42:13 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/06 18:58:33 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;

	if (((t_token *)tmp->content)->token == PIPE)
		ft_exit(data, "Invalid syntax: Wrong token", EXIT_FAILURE, NULL);
	while (tmp->next)
	{
		token = (t_token *)tmp->content;
		if (token->token == PIPE
			&& ((t_token *)tmp->next->content)->token == PIPE)
			ft_exit(data, "Invalid syntax: Wrong token", EXIT_FAILURE, NULL);
		if (is_redir(token->str)
			&& is_redir(((t_token *)tmp->next->content)->str))
			ft_exit(data, "Invalid syntax: Wrong token", EXIT_FAILURE, NULL);
		tmp = tmp->next;
	}
}