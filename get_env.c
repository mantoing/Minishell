/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:25:45 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 10:47:18 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <string.h>


static int	check_name(char *target)
{
	int	i;

	i = 0;
	if (*(target) == '?')
		return (1);
	while (*(target + i))
	{
		if (!(ft_isdigit(*(target + i)) || ft_isalpha(*(target + i)) \
					|| *(target + i) == '_'))
			return (i);
		i++;
	}
	return (i);
}

static char	*get_last_exit_code(t_info *info)
{
	if (g_signal)
	{
		info->exit_code = 1;
		g_signal = 0;
	}
	return (ft_itoa(info->exit_code));
}

char	*get_env(t_info *info, char *target, int *i)
{
	char	*str;
	char	*name;
	int		len;
	t_node	*temp;

	*i += 1;
	str = ft_strdup("");
	if (ft_isdigit(*(target + *i)))
		return (str);
	len = check_name(target + *i);
	name = ft_substr(target + *i, 0, len);
	*i += len - 1;
	temp = info->env_stack->head.next;
	while (temp != &info->env_stack->tail)
	{
		if (!ft_strcmp(name, temp->env_name))
		{
			free(str);
			free(name);
			return (ft_strdup(temp->env_value));
		}
		temp = temp->next;
	}
	if (*name == '?')
	{
		free(str);
		free(name);
		return (get_last_exit_code(info));
	}
	return (str);
}

char	*get_env_value(t_info *info, char *name)
{
	t_node	*temp;

	temp = info->env_stack->head.next;
	while (temp != &info->env_stack->tail)
	{
		if (!ft_strcmp(temp->env_name, name))
			return (ft_strdup(temp->env_value));
		temp = temp->next;
	}
	return (NULL);
}
