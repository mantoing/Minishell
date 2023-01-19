/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:53:41 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/19 16:21:10 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	check_valid_unset(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[++i])
	{
		j = -1;
		if ((!ft_isalpha(str[i][0])) && str[i][0] != '_')
			return (0);
		while (str[i][++j])
			if (!(ft_isalnum(str[i][j]) || str[i][j] == '_'))
				return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}

static void	del_env(t_info *info, char *str)
{
	t_node	*temp;
	t_node	*target;

	target = info->env_stack->head.next;
	while (target != &info->env_stack->tail)
	{
		if (!ft_strcmp(str, target->env_name))
		{
			temp = target;
			target->prev->next = target->next;
			target->next->prev = target->prev;
			target = target->next;
			free(temp->env_name);
			free(temp->env_value);
			free(temp);
			temp = NULL;
			break ;
		}
		else
			target = target->next;
	}
}

void	ft_unset(char **arg, t_info *info)
{
	int	i;

	if (arg[1] == NULL)
		return ;
	else
	{
		i = 1;
		if (!check_valid_unset(arg))
		{
			info->exit_code = print_err_with_exit_num("unset", arg[i], \
					"not a valid identifier", 1);
			return ;
		}
		while (arg[i] != NULL)
		{
			del_env(info, arg[i]);
			i++;
		}
	}
	g_signal = 0;
}
