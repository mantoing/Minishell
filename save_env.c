/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:59:29 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/09 17:31:27 by suhkim           ###   ########.fr       */
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

int	save_env(char **env, t_stack *env_stack)
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
			push_front_env(env_stack, ft_substr(*(env + i), 0,\
						pos - *(env + i)), ft_substr(*(env + i),\
						pos + 1 - *(env + i), len));
		i++;
	}
	remove_oldpwd(env_stack);
	return (1);
}
