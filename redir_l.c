/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:51:16 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/20 01:45:33 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <errno.h>

static int	valid_redir_l(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

int	redir_l(t_info *info, t_token *target)
{
	int		fd;

	if (valid_redir_l(info, target))
	{
		if (access(target->next->token, F_OK) != -1 && access(\
					target->next->token, R_OK) == -1)
		{
			info->exit_code = print_err_with_exit_num(target->next->token, \
					"Permission denied", NULL, 1);
			return (0);
		}
		fd = open(target->next->token, O_RDONLY);
		if (fd < 0)
		{
			info->exit_code = print_err_with_exit_num(target->next->token, \
					strerror(errno), NULL, 1);
			return (0);
		}
		ft_dup2(fd, STDIN_FILENO);
	}
	else
		return (0);
	return (1);
}
