/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:59:29 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/18 05:06:07 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
		push_front(env_stack, ft_substr(*(env + i), 0, pos - *(env + i)) \
				, ft_substr(*(env + i), pos + 1 - *(env + i), len));
		i++;
	}
	return (1);
}
