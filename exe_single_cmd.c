/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 06:48:27 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/25 21:35:53 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exe_single_cmd(t_info *info, t_token *temp)
{
	char	**arg;
	pid_t	pid;
	int		temp_fd_out;
	int		temp_fd_in;

	temp_fd_out = dup(STDOUT_FILENO);
	temp_fd_in = dup(STDIN_FILENO);
	arg = check_redirection(info, temp);
	if (!is_empty_arg(arg))
	{
		if (check_builtin(*(arg)))
			exe_builtin(info, arg);
		else
		{
			set_signal("IGNORE");
			pid = fork();
			if (pid == 0)
			{
				set_signal("DEFAULT");
				execve(check_absol_path(arg, info), arg, \
						change_list_to_arr_env(info));
				if (arg)
					free_arg(arg, cnt_arg_arr_size(arg));
				exit(1);
			}
		}
	}
	if (arg)
		free_arg(arg, cnt_arg_arr_size(arg));
	dup2(temp_fd_out, STDOUT_FILENO);
	dup2(temp_fd_in, STDIN_FILENO);
}
