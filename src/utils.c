/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/06 15:19:04 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

t_list	*search_token(t_list *tokens, int search)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == search)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**list_to_tab(t_list *lst)
{
	int		i;
	char	**tab;
	t_list	*tmp;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		tab[i++] = (char *)tmp->content;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	vnb(char *s)
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

void	ft_numeric(int exit_code, t_data *data, char *str, char **args)
{
	char	*str2;

	str2 = ft_strdup(args[1]);
	exit_cmd(exit_code, data, str, args);
	printf("bash: exit: %s: numeric argument required\n", str2);
	free(str2);
}

void print_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == CMD)
			printf("CMD ");
		else if (token->token == WORD)
			printf("WORD ");
		else if (token->token == PIPE)
			printf("PIPE ");
		else if (token->token == REDIR_IN)
			printf("REDIR_IN ");
		else if (token->token == REDIR_OUT)
			printf("REDIR_OUT ");
		else if (token->token == D_REDIR_IN)
			printf("D_REDIR_IN ");
		else if (token->token == D_REDIR_OUT)
			printf("D_REDIR_OUT ");
		tmp = tmp->next;
	}
	printf("\n");
}

void	print_str_tokens(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s\t", ((t_token *)tmp->content)->str);
		tmp = tmp->next;
	}
	printf("\n");
}