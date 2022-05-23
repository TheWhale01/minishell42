/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:56:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/23 14:40:41 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// O_CREAT | O_WRONLY | O_TRUNC
// O_CREAT | O_WRONLY | O_APPEND
void	redir_out(t_data *data, char *filename, int mode)
{
	int	file_fd;

	data->fd_out = dup(STDOUT);
	file_fd = open(filename, mode, 0644);
	dup2(file_fd, STDOUT);
	close(file_fd);
}

void	make_redirs(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == REDIR_OUT)
			redir_out(data, ((t_token *)tmp->next->content)->str,
				O_CREAT | O_WRONLY | O_TRUNC);
		else if (token->token == D_REDIR_OUT)
			redir_out(data, ((t_token *)tmp->next->content)->str,
				O_CREAT | O_WRONLY | O_APPEND);
		tmp = tmp->next;
	}
}

void	restore_redirs(t_data *data)
{
	if (data->fd_in != STDIN)
		dup2(data->fd_in, STDIN);
	if (data->fd_out != STDOUT)
		dup2(data->fd_out, STDOUT);
}
