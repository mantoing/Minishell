/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:25:45 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/25 02:33:16 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <string.h>


int	check_name(char *target)
{
	int	i;

	i = 0;
	while (*(target + i))
	{
		if (!(ft_isdigit(*(target + i)) || ft_isalpha(*(target + i))))
			return (i);
		i++;
	}
	return (i);
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
		if (!ft_strncmp(name, temp->env_name, ft_strlen(temp->env_name)))
			return (ft_strdup(temp->env_value));
		temp = temp->next;
	}
	return (str);
}
