/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/13 11:56:48 by hubretec         ###   ########.fr       */
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
		if (!ft_strcmp(data.line, "exit"))
			exit_cmd(EXIT_SUCCESS, &data);
		lst = format(data.line);
		print_lst(lst);
		tokenize(&data, lst);
		expander(&data);
		print_tokens(data.tokens, 0);
		free(data.line);
	}
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_list	*list;

// 	(void) envp;
// 	(void) ac;
// 	(void) av;
// 	list = create_list(envp);
// 	ft_env(&list);
// 	free_env(list);
// 	//ft_export(list, 's');
// 	return (0);
// }
