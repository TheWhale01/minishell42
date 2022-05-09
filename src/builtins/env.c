/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:06:23 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/23 15:35:59 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    lstadd_back(t_env **env, t_env *tmp)
{
    t_env    *end;

    end = *env;
    while (end->next)
        end = end->next;
    end->next = tmp;
}

t_env    *ft_lstnew(char *tmp)
{
    t_env    *env;

    env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    env->var = tmp;
    env->next = NULL;
    return (env);
}

t_env    *create_env(char **envp)
{
    t_env    *env;
    t_env    *tmp;
    int        i;

    i = 1;
    if (!*envp || !(**envp))
    {
        env = ft_lstnew(NULL);
        return (env);
    }
    env = ft_lstnew(envp[0]);
    while (envp[i])
    {
        tmp = ft_lstnew(envp[i]);
        lstadd_back(&env, tmp);
        i++;
    }
    return (env);
}

void    ft_env(t_env **env)
{
    t_env    *tmp;

    tmp = *env;
    if ((*env)->var)
    {
        while (tmp)
        {
            printf("%s\n", tmp->var);
            tmp = tmp->next;
        }
    }
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*v;

	tmp = env;
	while (tmp)
	{
		v = tmp->next;
		free(tmp);
		tmp = v;
	}
	env = NULL;
}

int    main(int ac, char **av, char **envp)
{
    t_env    *env;

    (void) envp;
    (void) ac;
    (void) av;
    env = create_env(envp);
    ft_env(&env);
    free_env(env);
   //ft_export(env, 's');
    return (0);
}
