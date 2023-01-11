/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:42:13 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/12 05:54:42 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_target_long(char *arg)
{
	long long	ans;
	int			sign;
	int			count;

	count = 0;
	ans = 0;
	sign = 1;
	while (*arg == ' ' || *arg == '\t' || *arg == '\v' || *arg == '\r'
		|| *arg == '\n' || *arg == '\f')
		arg++;
	if (*arg == '-' || *arg == '+')
		if (*(arg++) == '-')
			sign = -1;
	while (++count && *arg && *arg >= '0' && *arg <= '9')
	{
		ans = 10 * ans + (*arg++ - '0');
		if ((count > 19 && sign == -1) || (ans < 0 && sign == -1))
			return (0);
		else if ((count > 19 && sign == 1) || (ans < 0 && sign == 1))
			return (0);
	}
	return (1);
}

int	check_valid_arg_exit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && (*(arg + i) == '+' || *(arg + i) == '-'))
			i++;
		if (!ft_isdigit(*(arg + i)))
			return (-1);
		i++;
	}
	if (!check_target_long(arg))
		return (-2);
	return (1);
}

void	ft_exit(char **arg, int pipe)
{
	int	errno;

	if (!arg[1])
	{
		if (!pipe)
			printf("exit\n");
		exit(0);
	}
	if (check_valid_arg_exit(arg[1]) < 0)
	{
		print_err("exit", arg[1], "numeric argument required");
		errno = (char)ft_strtol(arg[1]);
		exit(errno);
	}
	if (arg[2])
	{
		exit_with_err("exit", "too many arguments", 1, 1);
		// not correct
		errno = 1;
		if (pipe)
			exit(errno);
		return ;
	}
	if (arg[1])
		errno = (char)ft_strtol(arg[1]);
	if (!pipe)
		printf("exit\n");
	exit(errno);
}
