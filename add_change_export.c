/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_change_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:51:09 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/25 22:27:53 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void change_env(char *value, t_node *env)
{
	free(env->env_value);
	env->env_value = ft_strdup(value);
	return ;
}

static int	push_non_value_env(t_stack *env_stack, char *name)
{
	if (!push_back_env(env_stack, name, NULL))
		return (-1);
	return (0);
}

int	add_change_export(char **arg, t_info *info)
{
	t_node *env;
	int		len;
	char	*pos;
	char	*name;
	char	*value;

	len = ft_strlen(arg[1]);
	pos = ft_strchr(arg[1], '=');
	name = ft_substr(arg[1], 0, pos - arg[1]);
	if (!pos)
		return (push_non_value_env(info->env_stack, name));
	value = ft_substr(arg[1], pos + 1 - arg[1], len);
	env = info->env_stack->head.next;
	while (env != &info->env_stack->tail)
	{
		if (!ft_strncmp(name, env->env_name, ft_strlen(env->env_name)))
		{
			change_env(value, env);
			return (0);
		}
		env = env->next;
	}
	push_back_env(info->env_stack, name, value);
	return (0);
}
