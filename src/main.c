/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/11 16:24:51 by jrossett         ###   ########.fr       */
=======
/*   Updated: 2022/05/13 11:56:48 by hubretec         ###   ########.fr       */
>>>>>>> 6785dee8e7b5d753dfee3092bbcd123b3a99010f
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

<<<<<<< HEAD
	(void) envp;
	(void) ac;
	(void) av;
	list = create_list(envp);
	//ft_env(&list);
	//free_list(list);
	ft_export(list, "export e=edwed dewed  dewde dewded   ");
=======
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
>>>>>>> 6785dee8e7b5d753dfee3092bbcd123b3a99010f
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
