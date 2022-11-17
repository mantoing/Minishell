/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:59:29 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/18 00:03:47 by jaeywon          ###   ########.fr       */
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
		push_back(env_stack, ft_substr(*(env + i), 0, pos - *(env + i)) \
				, ft_substr(*(env + i), pos - *(env + i), len));
		i++;
	}
	return (1);
}
