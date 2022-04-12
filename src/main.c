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
	t_data	data;

	(void)ac;
	(void)av;
	data.path = get_path_env(env);
	while (1)
	{
		ft_putstr_fd("minishell> ", STDIN);
		data.line = get_next_line(STDIN);
		data.tokens = tokenize(ft_split(data.line, ' '), data.path);
		if (!data.tokens)
			printf("Error\n");
		else
			print_tokens(data.tokens);
		if (!ft_strcmp(data.line, "exit\n"))
			exit_cmd(EXIT_SUCCESS, &data);
		free(data.line);
	}
	return (0);
}
