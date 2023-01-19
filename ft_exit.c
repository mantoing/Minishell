/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:42:13 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 23:18:19 by suhkim           ###   ########.fr       */
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

static void	sub_ft_exit(t_info *info, char **arg, int pipe)
{
	if (!arg[1])
	{
		if (!pipe)
			printf("exit\n");
		exit(0);
	}
	if (check_valid_arg_exit(arg[1]) < 0)
	{
		info->exit_code = print_err_with_exit_num("exit", arg[1], \
				"numeric argument required", 255);
		exit(info->exit_code);
	}
}

void	ft_exit(t_info *info, char **arg, int pipe)
{
	sub_ft_exit(info, arg, pipe);
	if (arg[2])
	{
		info->exit_code = print_err_with_exit_num("exit", \
				"too many arguments", NULL, 1);
		if (pipe)
			exit(info->exit_code);
		return ;
	}
	if (arg[1])
		info->exit_code = (char)ft_strtol(arg[1]);
	if (!pipe)
		printf("exit\n");
	exit(info->exit_code);
}
