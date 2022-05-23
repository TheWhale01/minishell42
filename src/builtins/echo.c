/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:27:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/23 14:38:59 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_list	*tokens, int opt)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	token = tmp->content;
	while (tmp && (token->token == CMD
			|| token->token == VAR || token->token == WORD))
	{
		printf("%s", token->str);
		tmp = tmp->next;
		if (tmp)
		{
			token = (t_token *)tmp->content;
			printf(" ");
		}
	}
	if (!opt)
		printf("\n");
}
