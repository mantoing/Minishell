/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:31:40 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/22 21:21:18 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exe_builtin(t_info *info, char **arg)
{
	if (!ft_strcmp(*(arg), "echo"))
		ft_echo(arg);
	else if (!ft_strcmp(*(arg), "env"))
		ft_env(info);
	else if (!ft_strcmp(*(arg), "export"))
		ft_export(arg, info);
	else if (!ft_strcmp(*(arg), "unset"))
		ft_unset(arg, info);
	else if (!ft_strcmp(*(arg), "cd"))
		ft_cd(arg, info);
	else if (!ft_strcmp(*(arg), "pwd"))
		ft_pwd();
//	else if (!ft_strcmp(*(arg), "exit"))
//		ft_exit();
}
