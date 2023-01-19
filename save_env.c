/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:59:29 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 16:19:08 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	remove_oldpwd(t_stack *env_stack)
{
	t_node	*temp;

	temp = env_stack->head.next;
	while (temp != &env_stack->tail)
	{
		if (!ft_strcmp(temp->env_name, "OLDPWD"))
		{
			free(temp->env_value);
			temp->env_value = NULL;
			break ;
		}
		temp = temp->next;
	}
}

static void	save_home_dir(t_info *info)
{
	t_node	*temp;

	temp = info->env_stack->head.next;
	while (temp != &info->env_stack->tail)
	{
		if (!ft_strcmp(temp->env_name, "HOME"))
			break ;
		temp = temp->next;
	}
	info->home_dir = ft_strdup(temp->env_value);
}

int	save_env(char **env, t_info *info)
{
	char	*pos;
	int		i;
	int		len;

	i = 0;
	while (*(env + i))
	{
		len = ft_strlen(*(env + i));
		pos = ft_strchr(*(env + i), '=');
		if (pos)
			push_front_env(info->env_stack, ft_substr(*(env + i), 0, \
						pos - *(env + i)), ft_substr(*(env + i), \
						pos + 1 - *(env + i), len));
		i++;
	}
	remove_oldpwd(info->env_stack);
	save_home_dir(info);
	return (1);
}
