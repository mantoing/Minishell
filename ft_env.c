/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:21:41 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/18 11:25:02 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '=')
			return (1);
	return (0);
}

int	ft_env(t_info *info)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = change_list_to_arr_env(info);
	while (env_arr[i] != NULL)
	{
		if (check_equal(env_arr[i]))
			printf("%s\n", env_arr[i]);
		i++;
	}
	free_temp(env_arr);
	return (1);
}
