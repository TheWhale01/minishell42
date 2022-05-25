/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:56:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/25 11:26:17 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in(t_data *data, char *filename)
{
	int	file_fd;

	data->fd_in = dup(STDIN);
	file_fd = open(filename, O_RDONLY, 0644);
	dup2(file_fd, STDIN);
	close(file_fd);
}

void	redir_out(t_data *data, char *filename, int mode)
{
	int	file_fd;

	data->fd_out = dup(STDOUT);
	if (mode == D_REDIR_OUT)
		file_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(file_fd, STDOUT);
	close(file_fd);
}

void	make_redirs(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	while (tmp && ((t_token *)tmp->content)->token != PIPE)
	{
		token = (t_token *)tmp->content;
		if (token->token == REDIR_OUT || token->token == D_REDIR_OUT)
			redir_out(data, ((t_token *)tmp->next->content)->str, token->token);
		else if (token->token == REDIR_IN)
			redir_in(data, ((t_token *)tmp->next->content)->str);
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
