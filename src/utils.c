/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/08 08:57:29 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	tablen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	*free_tab(void	**ptr)
{
	unsigned char	**tab;

	tab = (unsigned char **)ptr;
	while (*tab)
		free(*(tab++));
	free(tab);
	return (NULL);
}

char	**get_path_env(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			return (ft_split(&((*env)[5]), ':'));
		env++;
	}
	return (NULL);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].str)
	{
		if (tokens[i].token == CMD)
			printf("CMD ");
		else if (tokens[i].token == VAR)
			printf("VAR ");
		else if (tokens[i].token == PIPE)
			printf("PIPE ");
		else if (tokens[i].token == D_PIPE)
			printf("D_PIPE ");
	}
	printf("\n");
}

// void	exit_msg(int exit_code, char *str, t_data *data)
// {
// 		grosse fonction pour free une potentielle structure data
// 		dans laquelle il y aura tout ce qu'on aura malloc comme ca
// 		on aura juste a check si les pointeurs ne sont pas null pour
// 		les free
// }