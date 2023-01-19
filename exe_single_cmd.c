/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 06:48:27 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/20 01:16:51 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static pid_t	sub_single_cmd(t_info *info, char **arg, pid_t pid)
{
	if (!is_empty_arg(arg))
	{
		if (check_builtin(*(arg)))
			exe_builtin(info, arg, 0);
		else
		{
			set_signal("IGNORE");
			pid = fork();
			if (pid == 0)
			{
				set_signal("DEFAULT");
				execve(check_absol_path(arg, info), arg, \
						change_list_to_arr_env(info));
				exit(info->exit_code);
			}
		}
	}
	return (pid);
}

pid_t	exe_single_cmd(t_info *info, t_token *temp)
{
	char	**arg;
	pid_t	pid;
	int		temp_fd_out;
	int		temp_fd_in;

	pid = 0;
	temp_fd_out = dup(STDOUT_FILENO);
	temp_fd_in = dup(STDIN_FILENO);
	arg = check_redirection(info, temp);
	pid = sub_single_cmd(info, arg, pid);
	if (arg)
		free_arg(arg, cnt_arg_arr_size(arg));
	ft_dup2(temp_fd_out, STDOUT_FILENO);
	ft_dup2(temp_fd_in, STDIN_FILENO);
	g_signal = 0;
	return (pid);
}
