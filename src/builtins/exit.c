/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:33:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/01 16:29:19 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

void	free_tokens(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		free(((t_token *)tmp->content)->str);
		tmp = tmp->next;
	}
	ft_lstclear(&tokens, free);
}

void	exit_cmd(int exit_code, t_data *data, char *str)
{
	restore_redirs(data);
	if (exit_code == EXIT_FAILURE && str)
		ft_putendl_fd(str, STDERR_FILENO);
	else if (exit_code == EXIT_SUCCESS && str)
		ft_putendl_fd(str, STDOUT_FILENO);
	free(data->line);
	ft_lstclear(&data->envp, free);
	free_tab(data->path);
	free_tokens(data->tokens);
	free(data->pwd);
	free(data->childs);
	exit(exit_code);
}
