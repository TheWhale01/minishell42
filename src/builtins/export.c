/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:32:32 by teambersaw        #+#    #+#             */
/*   Updated: 2022/04/23 15:14:51 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && (s1[i] == s2[i]))
		{
			i++;
		}
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
		return (0);
}

int	ft_len(t_env **env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char *ft_first(t_env **env)
{
	t_env	*tmp;
	char	*min;

	tmp = *env;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		if (strcmp(min, tmp->var) > 0)
			min = tmp->var;
	}
	printf("%s\n", min);
	return (min);
}

char	*ft_min(char *str, t_env **env)
{
	t_env	*tmp;
	char	*min;

	tmp = *env;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		if (strcmp(tmp->var, min) < 0 && strcmp(str, min) < 0)
			min = tmp->var;
	}
	return (min);
}

void	ft_env_sort(t_env **env)
{
	t_env	*tmp;
	char	*str;
	char	*min;
	int		i;

	i = -1;
	tmp = *env;
	min = ft_first(env);
	while (++i < ft_len(env))
	{
		tmp = *env;
		str = tmp->var;
		while (tmp->next)
		{
			tmp = tmp->next;
			if (strcmp(str, min) == 0)
				str = ft_min(min, env);
			else if (strcmp(tmp->var, str) < 0 && strcmp(min, tmp->var) < 0)
				str = tmp->var;
		}
		min = str;
		printf("%s\n", str);
	}
}
	
// }

// 	t_env	*tmp;
// 	char	*str;
// 	char	*min;
// 	int		i;

// 	i = -1;
// 	tmp = *env;
// 	min = NULL;
// 	while (++i < ft_len(env))
// 	{
// 		str = tmp->var;
// 		while (tmp && tmp->next)
// 		{
// 			tmp = tmp->next;
// 			if (ft_strcmp(str, tmp->var) > 0)
// 			{
// 				if (min)
// 				{
// 					if (ft_strcmp(str, min) > 0)
// 						str = tmp->var;
// 				}
// 				else
// 					str = tmp->var;
// 			}	
// 		}
// 		min = str;
// 		printf("%s\n", str);
// 	}

int	ft_export(t_env *env, char c)
{
	if (c == 's')
		ft_env_sort(&env);
	return (0);
}