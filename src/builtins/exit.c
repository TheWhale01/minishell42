/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:33:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/03 15:25:00 by jrossett         ###   ########.fr       */
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

void	exit_cmd(int exit_code, t_data *data, char *str, char **args)
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
	if (args)
		free(args);
}

size_t	ft_verif_exit(char *str) //return 1 si c est un nombre et 0 si pas un nombre
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

int	ft_nb_verif(char *s)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	str = ft_strdup(s + i);
	if ((str[0] == '-' || str[0] == '+') && ft_strlen(str) > 20)
	{
		free(str);
		return (0);
	}
	else if (ft_strlen(str) > 19 && str[0] != '-' && str[0] != '+')
	{
		free(str);
		return (0);
	}
	if (ft_atoll_ul(str))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}


int	ft_exit(t_data *data, char *str, int exit_code, char **args)
{
	long long	val;
	char		*str2;

	if (!args)
		exit_cmd(exit_code, data, str, NULL);
	else if (ft_len_double(args) == 1)
		exit_cmd(exit_code, data, str, args);
	else
	{
		if (ft_len_double(args) == 2 && ft_verif_exit(args[1])
			&& ft_nb_verif(args[1]))
		{
			val = ft_atoll_ul(args[1]);
			exit_cmd(exit_code, data, str, args);
			exit(val);
		}
		else if (!ft_verif_exit(args[1]) || !ft_nb_verif(args[1]))
		{
			str2 = ft_strdup(args[1]);
			exit_cmd(exit_code, data, str, args);
			printf("bash: exit: %s: numeric argument required\n", str2);
			free(str2);
		}
		else if (ft_len_double(args) > 2 && ft_verif_exit(args[1])
			&& ft_nb_verif(args[1]))
		{
			printf("exit\nbash: exit: too many arguments\n");
			data->rtn_val = 1;
			return (0);
		}
	}
	exit(exit_code);
}
