/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/08 09:13:05 by hubretec         ###   ########.fr       */
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
	printf("path : %s\n", *path);
	while (1)
	{
		ft_putstr_fd("minishell> ", STDIN);
		line = get_next_line(STDIN);
		if (!line)
			break ;
		tokens = tokenize(ft_split(line, ' '), path);
		if (!tokens)
			printf("Error in cmd\n");
		else
			print_tokens(tokens);
		free(line);
	}
	return (0);
}
