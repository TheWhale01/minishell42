/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:49:30 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/02 14:29:51 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| *str == '>' || *str == '<');
}

void	rm_heredoc(t_data *data)
{
	int		i;
	char	*filename;

	i = -1;
	while (++i < data->heredocs)
	{
		filename = ft_strjoin_free_s2("/tmp/minishell", ft_itoa(i));
		unlink(filename);
		free(filename);
	}
}

void	heredoc(t_data *data, char *eof)
{
	int		fd;
	char	*line;
	char	*filename;

	filename = ft_strjoin_free_s2("/tmp/minishell", ft_itoa(data->heredocs++));
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || !ft_strncmp(line, eof, ft_strlen(eof)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	free(filename);
	close(fd);
}
