/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:12:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/24 13:28:23 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_data *data)
{
	while (((t_token *)data->tokens->content)->token != CMD)
		data->tokens = data->tokens->next;
	if (is_builtin(((t_token *)data->tokens->content)->str))
		exec_builtin(data);
	else
		
}

void	exec(t_data *data)
{
	if (!search_token(data->tokens, PIPE))
	{
		make_redirs(data);
		exec_cmd(data);
		restore_redirs(data);
	}
}
