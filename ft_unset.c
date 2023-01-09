/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:53:41 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/22 21:45:16 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	check_valid_unset(char *str)
{
	int i;

	i = -1;
	if ((!ft_isalpha(str[0])) && str[0] != '_')
		return (0);
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}

static void	del_env(char *str, t_info *info)
{
	t_node	*cur;
	t_node	*temp;

	temp = &info->env_stack->head;
	cur = temp->next;
	while (cur != &info->env_stack->tail)
	{
		if (!ft_strcmp(str, cur->env_name))
		{
			temp->next = cur->next;
			free(cur->env_name);
			free(cur->env_value);
			free(cur);
			break ;
		}
		temp = cur;
		cur = cur->next;
	}
}

void ft_unset(char **arg, t_info *info)
{
	int	i;

	if (arg[1] == NULL)
		return ;
	else
	{
		i = 1;
		while (arg[i] != NULL)
		{
			if (check_valid_unset(arg[i]) == 1)
				del_env(arg[i], info);
			else
				printf("unset_error\n");
			i++;
		}
	}
}
