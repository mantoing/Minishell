/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list_to_arr_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 07:54:06 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/19 15:08:42 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	cnt_list_size(t_info *info)
{
	int		i;
	t_node	*temp;

	temp = info->env_stack->head.next;
	i = 0;
	while (temp != &info->env_stack->tail)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

static char	**assign_list(char **arr, char *line, int l_size, t_info *info)
{
	int		i;
	t_node	*tmp;

	i = 0;
	line = NULL;
	tmp = info->env_stack->head.next;
	while (i < l_size)
	{
		line = ft_strdup(tmp->env_name);
		if (tmp->env_value)
		{
			line = ft_strjoin(line, ft_strdup("="));
			line = ft_strjoin(line, ft_strdup(tmp->env_value));
		}
		arr[i] = ft_strdup(line);
		free(line);
		tmp = tmp->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	**change_list_to_arr_env(t_info	*info)
{
	char	**arr;
	int		i;
	int		list_size;
	char	*line;

	i = 0;
	line = NULL;
	list_size = cnt_list_size(info);
	arr = (char **)malloc(list_size * (sizeof(char *) + 1));
	if (!arr)
		return (NULL);
	arr = assign_list(arr, line, list_size, info);
	return (arr);
}
