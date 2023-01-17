/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_change_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:51:09 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/17 20:39:10 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void change_env(char *value, t_node *env)
{
	free(env->env_value);
	env->env_value = ft_strdup(value);
	return ;
}

static int	push_non_value_env(t_info *info, char *name)
{
	t_node *env;

	env = info->env_stack->head.next;
	while (env != &info->env_stack->tail)
	{
		if (!ft_strncmp(name, env->env_name, ft_strlen(env->env_name)))
			return (0);
		env = env->next;
	}
	if (!push_back_env(info->env_stack, name, NULL))
		return (-1);
	return (0);
}

static int	valid_export_arg(char *arg)
{
	int i;

	i = 0;
	if ((!ft_isalpha(arg[0])) && arg[0] != '_')
		return (0);
	while (arg[++i] && arg[i] != '=')
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
	if (i == 0)
		return (0);
	return (1);
}

static int	add_change_export(char *arg, t_info *info)
{
	t_node *env;
	int		len;
	char	*pos;
	char	*name;
	char	*value;

	len = ft_strlen(arg);
	pos = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, pos - arg);
	if (!pos)
		return (push_non_value_env(info, name));
	value = ft_substr(arg, pos + 1 - arg, len);
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

int	ft_export_with_arg(t_info *info, char **arg)
{
	int	i;
	int	errno;

	i = 0;
	while (arg[++i])
	{
		if (!valid_export_arg(arg[i]))
		{
			dprintf(2, "error123\n");
			continue ;
		}
		errno = add_change_export(arg[i], info);
		if (errno != 0)
			return (-1);
	}
	return (0);
}
