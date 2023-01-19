/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:32:27 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/20 01:31:52 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	option_n_echo(char *arg)
{
	int	i;

	i = 1;
	if (arg == NULL)
		return (1);
	if (ft_strncmp(arg, "-n", 2) != 0)
		return (1);
	++i;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **arg)
{
	int	i;
	int	flag;

	i = 1;
	if (arg[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	while (!option_n_echo(arg[i]))
	{
		flag = 1;
		i++;
	}
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag != 1)
		printf("\n");
	g_signal = 0;
	return (0);
}
