/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/08 15:45:16 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**path;
	t_token	*tokens;

	(void)ac;
	(void)av;
	path = get_path_env(env);
	while (1)
	{
		line = readline("minishell> ");
		tokens = tokenize(ft_split(line, ' '), path);
		if (!tokens)
			printf("Error\n");
		else
			print_tokens(tokens);
		free(line);
	}
	return (0);
}
