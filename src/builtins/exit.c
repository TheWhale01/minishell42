/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:33:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/08 17:15:42 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	if (tab)
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

void	exit_cmd(int exit_code, t_data *data, char *str, char **args)
{
	restore_redirs(data, 0);
	if (exit_code == EXIT_FAILURE && str)
		ft_putendl_fd(str, STDERR_FILENO);
	else if (exit_code == EXIT_SUCCESS && str)
		ft_putendl_fd(str, STDOUT_FILENO);
	free(data->line);
	ft_lstclear(&data->envp, free);
	free_tab(data->path);
	free_tokens(data->tokens);
	free(data->pwd);
	if (args)
		free(args);
}

size_t	vexit(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] == ' ')
		i++;
	if (str && (str[i] == '+' || str[i] == '-'))
		i++;
	if (str && str[i] == '\0')
		return (0);
	while (str && str[i] && ft_isdigit(str[i]))
		i++;
	if (ft_strlen(str) == i)
		return (1);
	return (0);
}

int	ft_exit(t_data *data, char *str, int exit_code, char **args)
{
	long long	val;

	if (!args)
		exit_cmd(exit_code, data, str, NULL);
	else if (ft_len_double(args) == 1)
		exit_cmd(exit_code, data, str, args);
	else
	{
		if (ft_len_double(args) == 2 && vexit(args[1]) && vnb(args[1]))
		{
			val = ft_atoll_ul(args[1]);
			exit_cmd(exit_code, data, str, args);
			exit(val);
		}
		else if (!vexit(args[1]) || !vnb(args[1]))
			ft_numeric(exit_code, data, str, args);
		else if (ft_len_double(args) > 2 && vexit(args[1]) && vnb(args[1]))
		{
			ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
			data->rtn_val = 1;
			return (0);
		}
	}
	exit(exit_code);
}
