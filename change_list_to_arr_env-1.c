/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_list_to_arr_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 07:54:06 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/30 08:15:48 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	cnt_list_size(t_info *env)
{
	int		i;
	t_node	*temp;

	temp = env->env_stack->head.next;
	i = 0;
	while (temp != &env->env_stack->tail)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**change_list_to_arr_env(t_info	*env)
{
	char	**arr;
	int		i;
	int		list_size;
	char	*line;
	t_node	*tmp;

	i = 0;
	line = NULL;
	tmp = env->env_stack->head.next;
	list_size = cnt_list_size(env);
	arr = (char **)malloc(list_size * (sizeof(char *) + 1));
	if (!arr)
		return (NULL);
	while (i < list_size)
	{
		line = ft_strdup(tmp->env_name);
		line = ft_strjoin(line, "=");
		line = ft_strjoin(line, tmp->env_value);
		arr[i] = ft_strdup(line);
		free(line);
		tmp = tmp->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}
