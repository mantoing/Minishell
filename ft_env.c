/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 06:21:41 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/01 18:33:40 by jaeywon          ###   ########.fr       */
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

int	ft_env(t_info *env)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = change_list_to_arr_env(env);
	printf("env_arr[0] = %s\n", env_arr[0]);
	while (env_arr[i] != NULL)
	{
		if (check_equal(env_arr[i]))
			printf("%s\n", env_arr[i]);
		i++;
	}
	free(env_arr);
	return (1);
}
