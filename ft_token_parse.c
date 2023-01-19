/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:52:42 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/20 01:16:51 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_token_parse(t_info *info, t_token *pipe, int *read_fd, int *write_fd)
{
	char	**arg;

	set_signal("DEFAULT");
	ft_close(read_fd[1]);
	ft_close(write_fd[0]);
	ft_dup2(read_fd[0], STDIN_FILENO);
	ft_dup2(write_fd[1], STDOUT_FILENO);
	arg = check_redirection(info, pipe);
	if (!is_empty_arg(arg))
	{
		if (check_builtin(*(arg)))
			exe_builtin(info, arg, 1);
		else
		{
			execve(check_absol_path(arg, info), arg, \
					change_list_to_arr_env(info));
		}
	}
	if (!is_empty_arg(arg))
		free_arg(arg, cnt_arg_arr_size(arg));
	g_signal = 0;
	exit(info->exit_code);
}
