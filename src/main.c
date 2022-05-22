/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/21 11:24:02 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *data)
{
	data->line = NULL;
	data->path = NULL;
	data->envp = NULL;
	data->tokens = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_list	*lst;

	(void)ac;
	(void)av;
	init(&data);
	data.envp = create_list(envp);
	data.path = get_path_env(envp);
	while (1)
	{
		data.line = readline("minishell> ");
		if (!check_quotes(data.line))
			exit_cmd(EXIT_FAILURE, &data,
				"Syntax Error: mismatched opening and closing quotes.");
		lst = format(data.line);
		tokenize(&data, lst);
		ft_lstclear(&lst, NULL);
		expander(&data);
		//print_tokens(data.tokens, 1);
		if (!ft_strcmp(data.line, "exit"))
			exit_cmd(EXIT_SUCCESS, &data, NULL);
		ft_cd(&data);
		free_tokens(data.tokens);
	}
	return (0);
}
